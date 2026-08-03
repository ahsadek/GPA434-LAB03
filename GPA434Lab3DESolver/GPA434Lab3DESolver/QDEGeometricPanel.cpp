// Fichier : QDEGeometricPanel.cpp
// GPA434 - Laboratoire 3
// Création : Équipe GPA434, 2026/08/02
// Définition du panneau et de la stratégie d'optimisation géométrique.

#include "QDEGeometricPanel.h"

#include "LShapeBuilder.h"
#include "QImageViewer.h"
#include "RectangleBuilder.h"
#include "TriangleBuilder.h"

#include <EngineParameters.h>
#include <FitnessIdentity.h>
#include <OptimizationMaximization.h>
#include <Population.h>
#include <Solution.h>

#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSpinBox>
#include <QTransform>
#include <QVBoxLayout>

#include <algorithm>
#include <cmath>
#include <format>
#include <limits>


QDEGeometricPanel::QDEGeometricPanel(QWidget * parent)
    : QDESolutionPanel(parent)
    , mVisualizationLabel{ new QImageViewer }
    , mShapeComboBox{ new QComboBox }
    , mObstacleSpinBox{ new QSpinBox }
    , mRegenerateButton{ new QPushButton("Régénérer") }
    , mCanvasSize{ sCanvasWidth, sCanvasHeight }
{
    mPolygonBuilders.push_back(std::make_unique<TriangleBuilder>());
    mPolygonBuilders.push_back(std::make_unique<RectangleBuilder>());
    mPolygonBuilders.push_back(std::make_unique<LShapeBuilder>());

    for (std::unique_ptr<PolygonBuilder> const & builder : mPolygonBuilders) {
        mShapeComboBox->addItem(builder->name());
    }

    mObstacleSpinBox->setRange(sMinimumObstacleCount, sMaximumObstacleCount);
    mObstacleSpinBox->setValue(sDefaultObstacleCount);

    QHBoxLayout * obstacleLayout{ new QHBoxLayout };
    obstacleLayout->setContentsMargins(0, 0, 0, 0);
    obstacleLayout->addWidget(mObstacleSpinBox);
    obstacleLayout->addWidget(mRegenerateButton);

    QGroupBox * parameterGroupBox{ new QGroupBox("Paramètres") };
    QFormLayout * parameterLayout{ new QFormLayout(parameterGroupBox) };
    parameterLayout->addRow("Forme", mShapeComboBox);
    parameterLayout->addRow("Nombre d'obstacles", obstacleLayout);

    QGroupBox * visualizationGroupBox{ new QGroupBox("Visualisation") };
    QVBoxLayout * visualizationLayout{ new QVBoxLayout(visualizationGroupBox) };
    visualizationLayout->addWidget(mVisualizationLabel);

    QVBoxLayout * layout{ new QVBoxLayout(this) };
    layout->addWidget(parameterGroupBox);
    layout->addWidget(visualizationGroupBox);

    connect(mShapeComboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [this]() {
        drawVisualization(de::Population{});
        emit parameterChanged();
    });
    connect(mObstacleSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &QDEGeometricPanel::regenerateObstacles);
    connect(mRegenerateButton, &QPushButton::clicked,
            this, &QDEGeometricPanel::regenerateObstacles);

    regenerateObstacles();
}

de::SolutionStrategy* QDEGeometricPanel::buildSolution() const
{
    return new GeometricStrategy(mCanvasSize, mObstacles, selectedPolygon());
}

void QDEGeometricPanel::updateVisualization(QDEAdapter const & deAdapter)
{
    drawVisualization(deAdapter.actualPopulation());
}

void QDEGeometricPanel::regenerateObstacles()
{
    mObstacles.clear();
    mObstacles.reserve(static_cast<size_t>(mObstacleSpinBox->value()));

    QRandomGenerator * generator{ QRandomGenerator::global() };
    for (int i{}; i < mObstacleSpinBox->value(); ++i) {
        double x{ generator->generateDouble() * mCanvasSize.width() };
        double y{ generator->generateDouble() * mCanvasSize.height() };
        mObstacles.emplace_back(x, y);
    }

    drawVisualization(de::Population{});
    emit parameterChanged();
}

PolygonBuilder const & QDEGeometricPanel::selectedBuilder() const
{
    size_t index{ static_cast<size_t>(std::max(0, mShapeComboBox->currentIndex())) };
    return *mPolygonBuilders.at(index);
}

QPolygonF QDEGeometricPanel::selectedPolygon() const
{
    return selectedBuilder().createPolygon();
}

void QDEGeometricPanel::drawVisualization(de::Population const & population)
{
    QSize imageSize(static_cast<int>(mCanvasSize.width()),
                    static_cast<int>(mCanvasSize.height()));
    QPixmap pixmap(imageSize);
    pixmap.fill(QColor(248, 248, 248));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPolygonF basePolygon{ selectedPolygon() };
    QPen populationPen(QColor(90, 90, 90, 110));
    populationPen.setWidthF(1.0);
    painter.setPen(populationPen);
    painter.setBrush(Qt::NoBrush);

    size_t bestIndex{};
    double bestFitness{ std::numeric_limits<double>::lowest() };
    bool bestFound{};

    for (size_t i{}; i < population.size(); ++i) {
        if (population[i].size() != 4) {
            continue;
        }

        painter.drawPolygon(GeometricStrategy::transformPolygon(basePolygon, population[i]));
        if (!bestFound || population[i].fitness() > bestFitness) {
            bestIndex = i;
            bestFitness = population[i].fitness();
            bestFound = true;
        }
    }

    if (bestFound) {
        QPen bestPen(QColor(20, 100, 210));
        bestPen.setWidthF(4.0);
        painter.setPen(bestPen);
        painter.drawPolygon(GeometricStrategy::transformPolygon(basePolygon,
                                                                  population[bestIndex]));
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(210, 35, 35));
    double const obstacleRadius{ 3.5 };
    for (QPointF const & obstacle : mObstacles) {
        painter.drawEllipse(obstacle, obstacleRadius, obstacleRadius);
    }

    QPen canvasPen(QColor(30, 30, 30));
    canvasPen.setWidthF(2.0);
    painter.setPen(canvasPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(1.0, 1.0,
                            mCanvasSize.width() - 2.0,
                            mCanvasSize.height() - 2.0));

    mVisualizationLabel->setPixmap(pixmap);
}


QDEGeometricPanel::GeometricStrategy::GeometricStrategy(
    QSizeF const & canvasSize,
    std::vector<QPointF> const & obstacles,
    QPolygonF const & basePolygon)
    : SolutionStrategy(
        "Optimisation géométrique",
        "Trouver la plus grande forme pouvant être placée entre des obstacles.",
        "La solution détermine la position, la rotation et l'échelle uniforme "
        "d'un polygone placé dans un canevas rectangulaire.")
    , mCanvasSize{ canvasSize }
    , mObstacles{ obstacles }
    , mBasePolygon{ basePolygon }
    , mBaseArea{ polygonArea(basePolygon) }
{
    double const polygonSize{ polygonDiameter(mBasePolygon) };
    double const canvasSizeLimit{ std::hypot(mCanvasSize.width(), mCanvasSize.height()) };
    double const maximumScale{ polygonSize > 0.0 ? canvasSizeLimit / polygonSize : 0.0 };

    mSolutionDomain.resize(4);
    mSolutionDomain[0].set(0.0, mCanvasSize.width());
    mSolutionDomain[1].set(0.0, mCanvasSize.height());
    mSolutionDomain[2].set(0.0, 360.0);
    mSolutionDomain[3].set(0.0, maximumScale);

    setOptimizationStrategy(new de::OptimizationMaximization);
    setFitnessStrategy(new de::FitnessIdentity);
}

std::string QDEGeometricPanel::GeometricStrategy::toString(
    de::Solution const & solution) const
{
    return std::format(
        "Position : ({:.2f}, {:.2f})\n"
        "Rotation : {:.2f} degrés\n"
        "Échelle  : {:.4f}\n"
        "Aire     : {:.2f}",
        solution[0], solution[1], solution[2], solution[3], solution.objective());
}

de::EngineParameters QDEGeometricPanel::GeometricStrategy::engineParameters() const
{
    size_t const populationSize{ 60 };
    size_t const generationCount{ 400 };

    de::EngineParameters parameters;
    parameters.setPopulationSize(populationSize);
    parameters.setMaxGeneration(generationCount);
    return parameters;
}

QPolygonF QDEGeometricPanel::GeometricStrategy::transformPolygon(
    QPolygonF const & polygon,
    de::Solution const & solution)
{
    QTransform transform;
    transform.translate(solution[0], solution[1]);
    transform.rotate(solution[2]);
    transform.scale(solution[3], solution[3]);
    return transform.map(polygon);
}

double QDEGeometricPanel::GeometricStrategy::process(de::Solution const & solution)
{
    for (size_t i{}; i < mSolutionDomain.size(); ++i) {
        if (!mSolutionDomain[i].validate(solution[i])) {
            return 0.0;
        }
    }

    QPolygonF transformedPolygon{ transformPolygon(mBasePolygon, solution) };
    if (!isValid(transformedPolygon)) {
        return 0.0;
    }

    double const scale{ solution[3] };
    return mBaseArea * scale * scale;
}

bool QDEGeometricPanel::GeometricStrategy::isValid(QPolygonF const & polygon) const
{
    double const tolerance{ 1.0e-7 };
    QRectF canvasRect(QPointF(0.0, 0.0), mCanvasSize);
    QRectF toleratedCanvas{ canvasRect.adjusted(-tolerance, -tolerance,
                                                 tolerance, tolerance) };

    if (!toleratedCanvas.contains(polygon.boundingRect())) {
        return false;
    }

    for (QPointF const & obstacle : mObstacles) {
        if (isStrictlyInside(obstacle, polygon)) {
            return false;
        }
    }
    return true;
}

bool QDEGeometricPanel::GeometricStrategy::isStrictlyInside(
    QPointF const & point,
    QPolygonF const & polygon) const
{
    return !isOnBoundary(point, polygon)
        && polygon.containsPoint(point, Qt::OddEvenFill);
}

bool QDEGeometricPanel::GeometricStrategy::isOnBoundary(
    QPointF const & point,
    QPolygonF const & polygon) const
{
    double const tolerance{ 1.0e-7 };
    double const toleranceSquared{ tolerance * tolerance };

    for (qsizetype i{}; i < polygon.size(); ++i) {
        QPointF const start{ polygon[i] };
        QPointF const end{ polygon[(i + 1) % polygon.size()] };
        QPointF const edge{ end - start };
        QPointF const offset{ point - start };
        double const lengthSquared{ edge.x() * edge.x() + edge.y() * edge.y() };

        if (lengthSquared <= toleranceSquared) {
            continue;
        }

        double const crossProduct{ edge.x() * offset.y() - edge.y() * offset.x() };
        if (std::abs(crossProduct) > tolerance * std::sqrt(lengthSquared)) {
            continue;
        }

        double const dotProduct{ offset.x() * edge.x() + offset.y() * edge.y() };
        if (dotProduct >= -tolerance && dotProduct <= lengthSquared + tolerance) {
            return true;
        }
    }
    return false;
}

double QDEGeometricPanel::GeometricStrategy::polygonArea(QPolygonF const & polygon)
{
    double area{};
    for (qsizetype i{}; i < polygon.size(); ++i) {
        QPointF const & first{ polygon[i] };
        QPointF const & second{ polygon[(i + 1) % polygon.size()] };
        area += first.x() * second.y() - second.x() * first.y();
    }
    return std::abs(area) / 2.0;
}

double QDEGeometricPanel::GeometricStrategy::polygonDiameter(QPolygonF const & polygon)
{
    double diameter{};
    for (qsizetype i{}; i < polygon.size(); ++i) {
        for (qsizetype j{ i + 1 }; j < polygon.size(); ++j) {
            double const xDistance{ polygon[i].x() - polygon[j].x() };
            double const yDistance{ polygon[i].y() - polygon[j].y() };
            diameter = std::max(diameter, std::hypot(xDistance, yDistance));
        }
    }
    return diameter;
}
