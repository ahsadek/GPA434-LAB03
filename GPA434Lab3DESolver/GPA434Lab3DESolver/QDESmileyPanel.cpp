// Fichier : QDESmileyPanel.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/08
// Définition du panneau et de la stratégie du problème du visage souriant.

#include "QDESmileyPanel.h"

#include "CircleShape.h"
#include "HyperbolaShape.h"
#include "QImageViewer.h"

#include <EngineParameters.h>
#include <FitnessIdentity.h>
#include <OptimizationMinimization.h>
#include <Population.h>
#include <Solution.h>

#include <QFont>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QScrollBar>
#include <QVBoxLayout>

#include <format>


QColor const QDESmileyPanel::sBackgroundColor{ 248, 248, 248 };
QColor const QDESmileyPanel::sReferenceColor{ 30, 140, 60 };
QColor const QDESmileyPanel::sPopulationColor{ 90, 90, 90, 60 };
QColor const QDESmileyPanel::sBestSolutionColor{ 20, 100, 210 };
QColor const QDESmileyPanel::sBorderColor{ 30, 30, 30 };


QDESmileyPanel::QDESmileyPanel(QWidget * parent)
    : QDESolutionPanel(parent)
    , mVisualizationLabel{ new QImageViewer }
    , mHeadRadiusScrollBar{ nullptr }
    , mEyeRadiusScrollBar{ nullptr }
    , mEyeSpacingScrollBar{ nullptr }
    , mMouthCurvatureScrollBar{ nullptr }
    , mMouthWidthScrollBar{ nullptr }
    , mMouthOpeningScrollBar{ nullptr }
    , mRandomizeButton{ new QPushButton("Régénérer un visage") }
{
    int const minimumHeadRadius{ 60 };
    int const maximumHeadRadius{ 180 };
    int const defaultHeadRadius{ 120 };
    int const minimumEyeRadius{ 5 };
    int const maximumEyeRadius{ 40 };
    int const defaultEyeRadius{ 18 };
    int const minimumEyeSpacing{ 30 };
    int const maximumEyeSpacing{ 160 };
    int const defaultEyeSpacing{ 90 };
    int const minimumMouthCurvature{ 5 };
    int const maximumMouthCurvature{ 80 };
    int const defaultMouthCurvature{ 30 };
    int const minimumMouthWidth{ 40 };
    int const maximumMouthWidth{ 240 };
    int const defaultMouthWidth{ 140 };
    int const minimumMouthOpening{ 10 };
    int const maximumMouthOpening{ 100 };
    int const defaultMouthOpening{ 35 };

    QGroupBox * parameterGroupBox{ new QGroupBox("Paramètres") };
    QFormLayout * parameterLayout{ new QFormLayout(parameterGroupBox) };
    parameterLayout->addRow("Rayon de la tête",
        buildScrollBarLayout(mHeadRadiusScrollBar,
            minimumHeadRadius, maximumHeadRadius, defaultHeadRadius));
    parameterLayout->addRow("Rayon des yeux",
        buildScrollBarLayout(mEyeRadiusScrollBar,
            minimumEyeRadius, maximumEyeRadius, defaultEyeRadius));
    parameterLayout->addRow("Écartement des yeux",
        buildScrollBarLayout(mEyeSpacingScrollBar,
            minimumEyeSpacing, maximumEyeSpacing, defaultEyeSpacing));
    parameterLayout->addRow("Courbure de la bouche",
        buildScrollBarLayout(mMouthCurvatureScrollBar,
            minimumMouthCurvature, maximumMouthCurvature, defaultMouthCurvature));
    parameterLayout->addRow("Largeur de la bouche",
        buildScrollBarLayout(mMouthWidthScrollBar,
            minimumMouthWidth, maximumMouthWidth, defaultMouthWidth));
    parameterLayout->addRow("Ouverture de la bouche",
        buildScrollBarLayout(mMouthOpeningScrollBar,
            minimumMouthOpening, maximumMouthOpening, defaultMouthOpening));
    parameterLayout->addRow(mRandomizeButton);

    QGroupBox * visualizationGroupBox{ new QGroupBox("Visualisation") };
    QVBoxLayout * visualizationLayout{ new QVBoxLayout(visualizationGroupBox) };
    visualizationLayout->addWidget(mVisualizationLabel);

    QVBoxLayout * layout{ new QVBoxLayout(this) };
    layout->addWidget(parameterGroupBox);
    layout->addWidget(visualizationGroupBox);

    connect(mRandomizeButton, &QPushButton::clicked,
            this, &QDESmileyPanel::randomizeReference);

    referenceChanged();
}

de::SolutionStrategy* QDESmileyPanel::buildSolution() const
{
    return new SmileyStrategy(referenceParameters(), sSampleCount);
}

void QDESmileyPanel::updateVisualization(QDEAdapter const & deAdapter)
{
    drawVisualization(deAdapter.actualPopulation(),
                      deAdapter.currentGeneration());
}

void QDESmileyPanel::referenceChanged()
{
    drawVisualization(de::Population{});
    emit parameterChanged();
}

void QDESmileyPanel::randomizeReference()
{
    randomizeScrollBar(mHeadRadiusScrollBar);
    randomizeScrollBar(mEyeRadiusScrollBar);
    randomizeScrollBar(mEyeSpacingScrollBar);
    randomizeScrollBar(mMouthCurvatureScrollBar);
    randomizeScrollBar(mMouthWidthScrollBar);
    randomizeScrollBar(mMouthOpeningScrollBar);
}

void QDESmileyPanel::randomizeScrollBar(QScrollBar * scrollBar)
{
    QRandomGenerator * generator{ QRandomGenerator::global() };
    scrollBar->setValue(generator->bounded(scrollBar->minimum(),
                                           scrollBar->maximum() + 1));
}

// Le visage de référence est construit à partir des 6 paramètres du panneau.
// La tête est centrée dans le canevas; les yeux et la bouche sont placés
// proportionnellement au rayon de la tête.
std::vector<double> QDESmileyPanel::referenceParameters() const
{
    double const centerX{ sCanvasSize / 2.0 };
    double const centerY{ sCanvasSize / 2.0 };
    double const headRadius{ static_cast<double>(mHeadRadiusScrollBar->value()) };
    double const eyeRadius{ static_cast<double>(mEyeRadiusScrollBar->value()) };
    double const eyeSpacing{ static_cast<double>(mEyeSpacingScrollBar->value()) };
    double const mouthCurvature{ static_cast<double>(mMouthCurvatureScrollBar->value()) };
    double const mouthWidth{ static_cast<double>(mMouthWidthScrollBar->value()) };
    double const mouthOpening{ static_cast<double>(mMouthOpeningScrollBar->value()) };

    double const eyeY{ centerY - sEyeHeightRatio * headRadius };
    double const mouthY{ centerY + sMouthHeightRatio * headRadius };

    return { centerX, centerY, headRadius,
             centerX - eyeSpacing / 2.0, eyeY, eyeRadius,
             centerX + eyeSpacing / 2.0, eyeY, eyeRadius,
             centerX, mouthY, mouthCurvature, mouthOpening, mouthWidth };
}

// L'ordre des traits est le même que celui des 14 paramètres de la solution :
// tête (x, y, r), œil gauche (x, y, r), œil droit (x, y, r),
// bouche (x, y, courbure, ouverture, largeur).
std::vector<std::unique_ptr<FaceShape>> QDESmileyPanel::buildFaceShapes(
    std::vector<double> const & parameters)
{
    std::vector<std::unique_ptr<FaceShape>> shapes;
    shapes.push_back(std::make_unique<CircleShape>("Tête",
        parameters[0], parameters[1], parameters[2]));
    shapes.push_back(std::make_unique<CircleShape>("Œil gauche",
        parameters[3], parameters[4], parameters[5]));
    shapes.push_back(std::make_unique<CircleShape>("Œil droit",
        parameters[6], parameters[7], parameters[8]));
    shapes.push_back(std::make_unique<HyperbolaShape>("Bouche",
        parameters[9], parameters[10], parameters[11],
        parameters[12], parameters[13]));
    return shapes;
}

void QDESmileyPanel::drawFace(QPainter & painter,
                              std::vector<double> const & parameters,
                              int sampleCount)
{
    std::vector<std::unique_ptr<FaceShape>> shapes{ buildFaceShapes(parameters) };
    for (std::unique_ptr<FaceShape> const & shape : shapes) {
        shape->draw(painter, sampleCount);
    }
}

QHBoxLayout * QDESmileyPanel::buildScrollBarLayout(QScrollBar * & scrollBar,
                                                   int minimum,
                                                   int maximum,
                                                   int defaultValue)
{
    int const minimumWidth{ 150 };

    scrollBar = new QScrollBar;
    scrollBar->setOrientation(Qt::Horizontal);
    scrollBar->setRange(minimum, maximum);
    scrollBar->setValue(defaultValue);
    scrollBar->setMinimumWidth(minimumWidth);
    scrollBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QLabel * label{ new QLabel(QString::number(defaultValue)) };
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QHBoxLayout * layout{ new QHBoxLayout };
    layout->addWidget(scrollBar);
    layout->addWidget(label);

    connect(scrollBar, &QScrollBar::valueChanged,
            label, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(scrollBar, &QScrollBar::valueChanged,
            this, &QDESmileyPanel::referenceChanged);

    return layout;
}

void QDESmileyPanel::drawVisualization(de::Population const & population,
                                       size_t generation)
{
    int const pixmapWidth{ 2 * sCanvasSize + 3 * sMargin };
    int const pixmapHeight{ sCanvasSize + 2 * sMargin + sInfoLineHeight };
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(sBackgroundColor);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);

    QPointF const referenceOrigin(sMargin, sMargin);
    QPointF const populationOrigin(2.0 * sMargin + sCanvasSize, sMargin);
    std::vector<double> const reference{ referenceParameters() };
    int const sampleCount{ sSampleCount };

    // zones
    QPen borderPen(sBorderColor);
    borderPen.setWidthF(sBorderPenWidth);
    painter.setPen(borderPen);
    painter.drawRect(QRectF(referenceOrigin, QSizeF(sCanvasSize, sCanvasSize)));
    painter.drawRect(QRectF(populationOrigin, QSizeF(sCanvasSize, sCanvasSize)));

    // visage de référence
    // Le rognage limite chaque dessin à son canevas : les traits qui en
    // débordent existent toujours, seule leur partie intérieure est visible.
    QPen referencePen(sReferenceColor);
    referencePen.setWidthF(sReferencePenWidth);
    painter.setPen(referencePen);
    painter.save();
    painter.translate(referenceOrigin);
    painter.setClipRect(QRectF(0.0, 0.0, sCanvasSize, sCanvasSize));
    drawFace(painter, reference, sampleCount);
    painter.restore();

    // population complète et recherche de la meilleure solution
    // (minimisation : la plus petite erreur est la meilleure)
    QPen populationPen(sPopulationColor);
    populationPen.setWidthF(sPopulationPenWidth);
    painter.setPen(populationPen);

    size_t bestIndex{};
    double bestFitness{};
    bool bestFound{};

    painter.save();
    painter.translate(populationOrigin);
    painter.setClipRect(QRectF(0.0, 0.0, sCanvasSize, sCanvasSize));
    for (size_t i{}; i < population.size(); ++i) {
        if (population[i].size() != sParameterCount) {
            continue;
        }

        drawFace(painter, SmileyStrategy::solutionParameters(population[i]),
                 sampleCount);
        if (!bestFound || population[i].fitness() < bestFitness) {
            bestIndex = i;
            bestFitness = population[i].fitness();
            bestFound = true;
        }
    }

    if (bestFound) {
        QPen bestPen(sBestSolutionColor);
        bestPen.setWidthF(sBestSolutionPenWidth);
        painter.setPen(bestPen);
        drawFace(painter,
                 SmileyStrategy::solutionParameters(population[bestIndex]),
                 sampleCount);
    }
    painter.restore();

    // ligne d'information sous le canevas de la population : l'erreur totale
    // de la meilleure solution (sa fitness, en minimisation) et la génération
    if (bestFound) {
        QString const informationText{
            QString("Erreur totale : %1 — Génération : %2")
                .arg(QString::number(bestFitness, 'f', 2))
                .arg(generation) };
        QFont informationFont{ painter.font() };
        informationFont.setPointSize(sInfoFontSize);
        painter.setFont(informationFont);
        painter.setPen(borderPen);
        painter.drawText(QRectF(populationOrigin.x(), sMargin + sCanvasSize,
                                sCanvasSize, sInfoLineHeight),
                         Qt::AlignRight | Qt::AlignVCenter, informationText);
    }

    mVisualizationLabel->setPixmap(pixmap);
}


QDESmileyPanel::SmileyStrategy::SmileyStrategy(
    std::vector<double> const & referenceParameters,
    int sampleCount)
    : SolutionStrategy(
        "Visage souriant",
        "<p>Retrouver, par évolution différentielle, les 14 paramètres du "
        "visage souriant correspondant au visage de référence.</p>",
        "<p>Ce problème se résout dans un espace à 14 dimensions : "
        "la tête, l'œil gauche et l'œil droit sont des cercles (x, y, rayon), "
        "alors que la bouche est une branche d'hyperbole "
        "(x, y, courbure, ouverture, largeur).</p>"
        "<p>Le domaine des positions correspond au canevas du visage. "
        "Les rayons et les paramètres de la bouche sont bornés de façon à "
        "couvrir tous les visages de référence possibles.</p>"
        "<p>La fonction objective échantillonne des points sur chaque trait du "
        "visage candidat et calcule l'erreur quadratique moyenne avec les "
        "points correspondants du visage de référence. Une erreur de zéro "
        "signifie que le candidat reproduit exactement la référence : le "
        "problème est donc une minimisation.</p>")
    , mSampleCount{ sampleCount }
{
    std::vector<std::unique_ptr<FaceShape>> const referenceShapes{
        buildFaceShapes(referenceParameters) };
    for (std::unique_ptr<FaceShape> const & shape : referenceShapes) {
        mReferencePoints.push_back(shape->samplePoints(mSampleCount));
        mShapeNames.push_back(shape->name());
    }

    mSolutionDomain.resize(sParameterCount);
    mSolutionDomain[0].set(0.0, sCanvasSize);                       // tête x
    mSolutionDomain[1].set(0.0, sCanvasSize);                       // tête y
    mSolutionDomain[2].set(sMinimumHeadRadius, sMaximumHeadRadius); // tête r
    mSolutionDomain[3].set(0.0, sCanvasSize);                       // œil gauche x
    mSolutionDomain[4].set(0.0, sCanvasSize);                       // œil gauche y
    mSolutionDomain[5].set(sMinimumEyeRadius, sMaximumEyeRadius);   // œil gauche r
    mSolutionDomain[6].set(0.0, sCanvasSize);                       // œil droit x
    mSolutionDomain[7].set(0.0, sCanvasSize);                       // œil droit y
    mSolutionDomain[8].set(sMinimumEyeRadius, sMaximumEyeRadius);   // œil droit r
    mSolutionDomain[9].set(0.0, sCanvasSize);                       // bouche x
    mSolutionDomain[10].set(0.0, sCanvasSize);                      // bouche y
    mSolutionDomain[11].set(sMinimumCurvature, sMaximumCurvature);  // courbure
    mSolutionDomain[12].set(sMinimumOpening, sMaximumOpening);      // ouverture
    mSolutionDomain[13].set(sMinimumMouthWidth, sMaximumMouthWidth);// largeur

    setOptimizationStrategy(new de::OptimizationMinimization);
    setFitnessStrategy(new de::FitnessIdentity);
}

std::string QDESmileyPanel::SmileyStrategy::toString(
    de::Solution const & solution) const
{
    std::vector<double> const errors{ shapeErrors(solution) };
    double totalError{};
    for (double const error : errors) {
        totalError += error;
    }

    std::string text{ std::format("Erreur totale : {:.4f}", totalError) };
    for (size_t i{}; i < errors.size(); ++i) {
        text += std::format("\n - {:<12} : {:.4f}",
                            mShapeNames[i].toStdString(), errors[i]);
    }
    return text;
}

de::EngineParameters QDESmileyPanel::SmileyStrategy::engineParameters() const
{
    size_t const populationSize{ 100 };
    size_t const generationCount{ 800 };
    double const mutationFactor{ 0.35 };
    double const crossoverRate{ 0.80 };

    de::EngineParameters parameters;
    parameters.setPopulationSize(populationSize);
    parameters.setMaxGeneration(generationCount);
    parameters.setMutationFactor(mutationFactor);
    parameters.setCrossoverRate(crossoverRate);
    return parameters;
}

std::vector<double> QDESmileyPanel::SmileyStrategy::solutionParameters(
    de::Solution const & solution)
{
    std::vector<double> parameters(solution.size());
    for (size_t i{}; i < solution.size(); ++i) {
        parameters[i] = solution[i];
    }
    return parameters;
}

// L'erreur d'un trait est la distance quadratique moyenne entre les points
// correspondants des deux courbes. La moyenne rend l'erreur indépendante du
// nombre de points d'échantillonnage choisi.
double QDESmileyPanel::SmileyStrategy::shapeError(
    QPolygonF const & candidatePoints,
    QPolygonF const & referencePoints)
{
    if (candidatePoints.size() != referencePoints.size()
        || candidatePoints.isEmpty()) {
        return sInvalidSolutionError;
    }

    double errorSum{};
    for (qsizetype i{}; i < candidatePoints.size(); ++i) {
        double const deltaX{ candidatePoints[i].x() - referencePoints[i].x() };
        double const deltaY{ candidatePoints[i].y() - referencePoints[i].y() };
        errorSum += deltaX * deltaX + deltaY * deltaY;
    }
    return errorSum / candidatePoints.size();
}

double QDESmileyPanel::SmileyStrategy::process(de::Solution const & solution)
{
    for (size_t i{}; i < mSolutionDomain.size(); ++i) {
        if (!mSolutionDomain[i].validate(solution[i])) {
            return sInvalidSolutionError;
        }
    }

    std::vector<double> const errors{ shapeErrors(solution) };
    double totalError{};
    for (double const error : errors) {
        totalError += error;
    }
    return totalError;
}

std::vector<double> QDESmileyPanel::SmileyStrategy::shapeErrors(
    de::Solution const & solution) const
{
    std::vector<std::unique_ptr<FaceShape>> const candidateShapes{
        buildFaceShapes(solutionParameters(solution)) };

    std::vector<double> errors;
    for (size_t i{}; i < candidateShapes.size(); ++i) {
        errors.push_back(shapeError(candidateShapes[i]->samplePoints(mSampleCount),
                                    mReferencePoints[i]));
    }
    return errors;
}
