// Fichier : RectangleBuilder.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/02
// Définition du rectangle normalisé.

#include "RectangleBuilder.h"


QString RectangleBuilder::name() const
{
    return "Rectangle";
}

QPolygonF RectangleBuilder::createPolygon() const
{
    QPolygonF polygon;
    polygon << QPointF(-0.5, -0.35)
            << QPointF(0.5, -0.35)
            << QPointF(0.5, 0.35)
            << QPointF(-0.5, 0.35);
    return polygon;
}
