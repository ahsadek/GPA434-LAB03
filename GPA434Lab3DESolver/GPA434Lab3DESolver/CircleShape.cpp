// Fichier : CircleShape.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/07
// Définition du trait circulaire.

#include "CircleShape.h"

#include <QPainter>

#include <cmath>


CircleShape::CircleShape(QString const & name,
                         double centerX,
                         double centerY,
                         double radius)
    : FaceShape(name)
    , mCenterX{ centerX }
    , mCenterY{ centerY }
    , mRadius{ radius }
{
}

QPolygonF CircleShape::samplePoints(int sampleCount) const
{
    double const pi{ 3.14159265358979323846 };

    QPolygonF points;
    if (sampleCount <= 0) {
        return points;
    }

    // les points sont répartis uniformément sur la circonférence, toujours
    // à partir du même angle afin que deux cercles identiques produisent
    // exactement les mêmes points
    double const angleStep{ 2.0 * pi / sampleCount };
    for (int i{}; i < sampleCount; ++i) {
        double const angle{ i * angleStep };
        points << QPointF(mCenterX + mRadius * std::cos(angle),
                          mCenterY + mRadius * std::sin(angle));
    }
    return points;
}

void CircleShape::draw(QPainter & painter, int sampleCount) const
{
    // courbe fermée : le dernier point est relié au premier
    painter.drawPolygon(samplePoints(sampleCount));
}
