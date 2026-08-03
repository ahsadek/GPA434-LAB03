#pragma once
#ifndef RECTANGLE_BUILDER_H
#define RECTANGLE_BUILDER_H

// Fichier : RectangleBuilder.h
// GPA434 - Laboratoire 3
// Création : Équipe GPA434, 2026/08/02
// Créateur d'un rectangle normalisé.

#include "PolygonBuilder.h"


//! \brief Construit le rectangle offert par le problème géométrique.
class RectangleBuilder : public PolygonBuilder
{
public:
    RectangleBuilder() = default;
    RectangleBuilder(RectangleBuilder const &) = default;
    RectangleBuilder& operator=(RectangleBuilder const &) = default;
    ~RectangleBuilder() override = default;

    QString name() const override;
    QPolygonF createPolygon() const override;
};


#endif // RECTANGLE_BUILDER_H
