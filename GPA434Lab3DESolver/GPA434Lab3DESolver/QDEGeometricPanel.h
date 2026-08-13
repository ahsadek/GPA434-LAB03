#pragma once
#ifndef Q_DE_GEOMETRIC_PANEL_H
#define Q_DE_GEOMETRIC_PANEL_H

// Fichier : QDEGeometricPanel.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/03
// Panneau et stratégie du problème d'optimisation géométrique.

#include "PolygonBuilder.h"
#include "QDESolutionPanel.h"

#include <QColor>
#include <QPolygonF>
#include <QSizeF>

#include <memory>
#include <vector>


class QComboBox;
class QImageViewer;
class QPushButton;
class QSpinBox;

namespace de {
    class Population;
    class Solution;
}


//! \brief Configure et visualise le problème d'optimisation géométrique.
class QDEGeometricPanel : public QDESolutionPanel
{
    Q_OBJECT

public:
    QDEGeometricPanel(QWidget * parent = nullptr);
    QDEGeometricPanel(QDEGeometricPanel const &) = delete;
    QDEGeometricPanel& operator=(QDEGeometricPanel const &) = delete;
    ~QDEGeometricPanel() override = default;

    de::SolutionStrategy* buildSolution() const override;

public slots:
    void updateVisualization(QDEAdapter const & deAdapter) override;

private slots:
    void shapeSelectionChanged();
    void regenerateObstacles();

private:
    QImageViewer * mVisualizationLabel;
    QComboBox * mShapeComboBox;
    QSpinBox * mObstacleSpinBox;
    QPushButton * mRegenerateButton;
    QSizeF mCanvasSize;
    std::vector<QPointF> mObstacles;
    std::vector<std::unique_ptr<PolygonBuilder>> mPolygonBuilders;

    static constexpr int sCanvasWidth{ 800 };
    static constexpr int sCanvasHeight{ 600 };
    static constexpr int sMinimumObstacleCount{ 0 };
    static constexpr int sMaximumObstacleCount{ 100 };
    static constexpr int sDefaultObstacleCount{ 25 };
    static constexpr size_t sSolutionDimensionCount{ 4 };

    static constexpr double sObstacleRadius{ 3.5 };
    static constexpr double sPopulationPenWidth{ 1.0 };
    static constexpr double sBestSolutionPenWidth{ 4.0 };
    static constexpr double sCanvasBorderPenWidth{ 2.0 };
    static QColor const sBackgroundColor;
    static QColor const sPopulationColor;
    static QColor const sBestSolutionColor;
    static QColor const sObstacleColor;
    static QColor const sCanvasBorderColor;

    PolygonBuilder const & selectedBuilder() const;
    QPolygonF selectedPolygon() const;
    void drawVisualization(de::Population const & population);

    class GeometricStrategy;
};


//! \brief Définit le domaine et l'évaluation du problème géométrique.
class QDEGeometricPanel::GeometricStrategy : public de::SolutionStrategy
{
public:
    GeometricStrategy(QSizeF const & canvasSize,
                      std::vector<QPointF> const & obstacles,
                      QPolygonF const & basePolygon);
    GeometricStrategy(GeometricStrategy const &) = default;
    GeometricStrategy& operator=(GeometricStrategy const &) = delete;
    ~GeometricStrategy() override = default;

    std::string toString(de::Solution const & solution) const override;
    de::EngineParameters engineParameters() const override;

    static QPolygonF transformPolygon(QPolygonF const & polygon,
                                      de::Solution const & solution);

    DEFINE_OVERRIDE_CLONE_METHOD(GeometricStrategy)

protected:
    double process(de::Solution const & solution) override;

private:
    QSizeF mCanvasSize;
    std::vector<QPointF> mObstacles;
    QPolygonF mBasePolygon;
    double mBaseArea;

    static constexpr double sGeometryTolerance{ 1.0e-7 };

    bool isValid(QPolygonF const & polygon) const;
    bool isStrictlyInside(QPointF const & point, QPolygonF const & polygon) const;
    bool isOnBoundary(QPointF const & point, QPolygonF const & polygon) const;
    static double polygonArea(QPolygonF const & polygon);
    static double polygonDiameter(QPolygonF const & polygon);
};


#endif // Q_DE_GEOMETRIC_PANEL_H
