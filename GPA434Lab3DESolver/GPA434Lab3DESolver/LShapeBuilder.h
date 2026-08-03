#pragma once
#ifndef L_SHAPE_BUILDER_H
#define L_SHAPE_BUILDER_H

// Fichier : LShapeBuilder.h
// GPA434 - Laboratoire 3
// Création : Équipe GPA434, 2026/08/02
// Créateur d'un polygone concave en forme de L.

#include "PolygonBuilder.h"


//! \brief Construit la forme en L offerte par le problème géométrique.
class LShapeBuilder : public PolygonBuilder
{
public:
    LShapeBuilder() = default;
    LShapeBuilder(LShapeBuilder const &) = default;
    LShapeBuilder& operator=(LShapeBuilder const &) = default;
    ~LShapeBuilder() override = default;

    QString name() const override;
    QPolygonF createPolygon() const override;
};


#endif // L_SHAPE_BUILDER_H
