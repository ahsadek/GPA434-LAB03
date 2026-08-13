#pragma once
#ifndef Q_DE_SMILEY_PANEL_H
#define Q_DE_SMILEY_PANEL_H

// Fichier : QDESmileyPanel.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/08
// Panneau et stratégie du problème du visage souriant : la population
// évolue jusqu'à reproduire le visage de référence.

#include "FaceShape.h"
#include "QDESolutionPanel.h"

#include <QColor>

#include <memory>
#include <vector>


class QHBoxLayout;
class QImageViewer;
class QPainter;
class QPushButton;
class QScrollBar;

namespace de {
    class Population;
    class Solution;
}


//! \brief Configure et visualise le problème du visage souriant.
class QDESmileyPanel : public QDESolutionPanel
{
    Q_OBJECT

public:
    QDESmileyPanel(QWidget * parent = nullptr);
    QDESmileyPanel(QDESmileyPanel const &) = delete;
    QDESmileyPanel& operator=(QDESmileyPanel const &) = delete;
    ~QDESmileyPanel() override = default;

    de::SolutionStrategy* buildSolution() const override;

public slots:
    void updateVisualization(QDEAdapter const & deAdapter) override;

private slots:
    void referenceChanged();
    void randomizeReference();

private:
    QImageViewer * mVisualizationLabel;
    QScrollBar * mHeadRadiusScrollBar;
    QScrollBar * mEyeRadiusScrollBar;
    QScrollBar * mEyeSpacingScrollBar;
    QScrollBar * mMouthCurvatureScrollBar;
    QScrollBar * mMouthWidthScrollBar;
    QScrollBar * mMouthOpeningScrollBar;
    QPushButton * mRandomizeButton;

    static constexpr size_t sParameterCount{ 14 };
    static constexpr int sCanvasSize{ 400 };
    static constexpr int sMargin{ 20 };
    static constexpr int sInfoLineHeight{ 32 };
    static constexpr int sInfoFontSize{ 14 };
    static constexpr int sSampleCount{ 32 };
    static constexpr double sEyeHeightRatio{ 0.35 };
    static constexpr double sMouthHeightRatio{ 0.45 };

    static constexpr double sReferencePenWidth{ 2.0 };
    static constexpr double sPopulationPenWidth{ 1.0 };
    static constexpr double sBestSolutionPenWidth{ 2.5 };
    static constexpr double sBorderPenWidth{ 1.0 };
    static QColor const sBackgroundColor;
    static QColor const sReferenceColor;
    static QColor const sPopulationColor;
    static QColor const sBestSolutionColor;
    static QColor const sBorderColor;

    std::vector<double> referenceParameters() const;
    QHBoxLayout * buildScrollBarLayout(QScrollBar * & scrollBar,
                                       int minimum,
                                       int maximum,
                                       int defaultValue);
    void drawVisualization(de::Population const & population,
                           size_t generation = 0);
    static std::vector<std::unique_ptr<FaceShape>> buildFaceShapes(
        std::vector<double> const & parameters);
    static void drawFace(QPainter & painter,
                         std::vector<double> const & parameters,
                         int sampleCount);
    static void randomizeScrollBar(QScrollBar * scrollBar);

    class SmileyStrategy;
};


//! \brief Définit le domaine et l'évaluation du problème du visage souriant.
class QDESmileyPanel::SmileyStrategy : public de::SolutionStrategy
{
public:
    SmileyStrategy(std::vector<double> const & referenceParameters,
                   int sampleCount);
    SmileyStrategy(SmileyStrategy const &) = default;
    SmileyStrategy& operator=(SmileyStrategy const &) = delete;
    ~SmileyStrategy() override = default;

    std::string toString(de::Solution const & solution) const override;
    de::EngineParameters engineParameters() const override;

    static std::vector<double> solutionParameters(de::Solution const & solution);
    static double shapeError(QPolygonF const & candidatePoints,
                             QPolygonF const & referencePoints);

    DEFINE_OVERRIDE_CLONE_METHOD(SmileyStrategy)

protected:
    double process(de::Solution const & solution) override;

private:
    int mSampleCount;
    std::vector<QPolygonF> mReferencePoints;
    std::vector<QString> mShapeNames;

    static constexpr double sMinimumHeadRadius{ 10.0 };
    static constexpr double sMaximumHeadRadius{ 200.0 };
    static constexpr double sMinimumEyeRadius{ 2.0 };
    static constexpr double sMaximumEyeRadius{ 60.0 };
    static constexpr double sMinimumCurvature{ 1.0 };
    static constexpr double sMaximumCurvature{ 100.0 };
    static constexpr double sMinimumOpening{ 5.0 };
    static constexpr double sMaximumOpening{ 200.0 };
    static constexpr double sMinimumMouthWidth{ 20.0 };
    static constexpr double sMaximumMouthWidth{ 300.0 };
    static constexpr double sInvalidSolutionError{ 1.0e9 };

    std::vector<double> shapeErrors(de::Solution const & solution) const;
};


#endif // Q_DE_SMILEY_PANEL_H
