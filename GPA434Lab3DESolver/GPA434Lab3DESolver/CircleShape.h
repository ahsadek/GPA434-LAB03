#pragma once
#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

// Fichier : CircleShape.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/07
// Trait circulaire du visage : tête et yeux.

#include "FaceShape.h"


//! \brief Cercle défini par son centre et son rayon.
class CircleShape : public FaceShape
{
public:
    CircleShape(QString const & name, double centerX, double centerY, double radius);
    CircleShape(CircleShape const &) = default;
    CircleShape& operator=(CircleShape const &) = default;
    ~CircleShape() override = default;

    QPolygonF samplePoints(int sampleCount) const override;
    void draw(QPainter & painter, int sampleCount) const override;

private:
    double mCenterX;
    double mCenterY;
    double mRadius;
};


#endif // CIRCLE_SHAPE_H
