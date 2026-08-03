// Fichier : TriangleBuilder.cpp
// GPA434 - Laboratoire 3
// Création : Équipe GPA434, 2026/08/02
// Définition du triangle normalisé.

#include "TriangleBuilder.h"


QString TriangleBuilder::name() const
{
    return "Triangle";
}

QPolygonF TriangleBuilder::createPolygon() const
{
    QPolygonF polygon;
    polygon << QPointF(-0.5, 0.5)
            << QPointF(0.0, -0.5)
            << QPointF(0.5, 0.5);
    return polygon;
}
