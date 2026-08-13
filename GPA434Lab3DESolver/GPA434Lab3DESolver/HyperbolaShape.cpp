// Fichier : HyperbolaShape.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/08
// Définition du trait hyperbolique.

#include "HyperbolaShape.h"

#include <QPainter>

#include <cmath>


HyperbolaShape::HyperbolaShape(QString const & name,
                               double centerX,
                               double centerY,
                               double curvature,
                               double opening,
                               double width)
    : FaceShape(name)
    , mCenterX{ centerX }
    , mCenterY{ centerY }
    , mCurvature{ curvature }
    , mOpening{ opening }
    , mWidth{ width }
{
}

QPolygonF HyperbolaShape::samplePoints(int sampleCount) const
{
    QPolygonF points;
    if (sampleCount < 2 || mOpening <= 0.0) {
        return points;
    }

    // les points sont répartis uniformément sur la largeur de la bouche,
    // centrée sur le sommet (mCenterX, mCenterY)
    double const startX{ mCenterX - mWidth / 2.0 };
    double const stepX{ mWidth / (sampleCount - 1) };
    for (int i{}; i < sampleCount; ++i) {
        double const x{ startX + i * stepX };
        double const normalizedX{ (x - mCenterX) / mOpening };
        double const y{ mCenterY
            - mCurvature * (std::sqrt(1.0 + normalizedX * normalizedX) - 1.0) };
        points << QPointF(x, y);
    }
    return points;
}

void HyperbolaShape::draw(QPainter & painter, int sampleCount) const
{
    // courbe ouverte : les extrémités ne sont pas reliées
    painter.drawPolyline(samplePoints(sampleCount));
}
