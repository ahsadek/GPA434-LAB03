// Fichier : LShapeBuilder.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/02
// Définition du polygone concave en forme de L.

#include "LShapeBuilder.h"


QString LShapeBuilder::name() const
{
    return "Forme en L";
}

QPolygonF LShapeBuilder::createPolygon() const
{
    QPolygonF polygon;
    polygon << QPointF(-0.5, -0.5)
            << QPointF(-0.1, -0.5)
            << QPointF(-0.1, 0.1)
            << QPointF(0.5, 0.1)
            << QPointF(0.5, 0.5)
            << QPointF(-0.5, 0.5);
    return polygon;
}
