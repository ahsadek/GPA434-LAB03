#pragma once
#ifndef HYPERBOLA_SHAPE_H
#define HYPERBOLA_SHAPE_H

// Fichier : HyperbolaShape.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/08
// Trait hyperbolique du visage : la bouche.

#include "FaceShape.h"


//! \brief Branche d'hyperbole centrée sur son sommet (h, k).
//! La courbe suit y(x) = k - a * (sqrt(1 + ((x - h) / b)²) - 1) où :
//! - (h, k) est le sommet de la bouche;
//! - a est la courbure (hauteur des coins par rapport au sommet);
//! - b est l'ouverture (plus b est grand, plus la courbe est plate);
//! - w est la largeur totale échantillonnée.
//! En coordonnées d'écran (y vers le bas), les coins remontent : un sourire.
class HyperbolaShape : public FaceShape
{
public:
    HyperbolaShape(QString const & name,
                   double centerX,
                   double centerY,
                   double curvature,
                   double opening,
                   double width);
    HyperbolaShape(HyperbolaShape const &) = default;
    HyperbolaShape& operator=(HyperbolaShape const &) = default;
    ~HyperbolaShape() override = default;

    QPolygonF samplePoints(int sampleCount) const override;
    void draw(QPainter & painter, int sampleCount) const override;

private:
    double mCenterX;
    double mCenterY;
    double mCurvature;
    double mOpening;
    double mWidth;
};


#endif // HYPERBOLA_SHAPE_H
