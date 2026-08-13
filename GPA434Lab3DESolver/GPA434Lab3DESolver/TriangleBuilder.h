#pragma once
#ifndef TRIANGLE_BUILDER_H
#define TRIANGLE_BUILDER_H

// Fichier : TriangleBuilder.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/01
// Créateur d'un triangle normalisé.

#include "PolygonBuilder.h"


//! \brief Construit le triangle offert par le problème géométrique.
class TriangleBuilder : public PolygonBuilder
{
public:
    TriangleBuilder() = default;
    TriangleBuilder(TriangleBuilder const &) = default;
    TriangleBuilder& operator=(TriangleBuilder const &) = default;
    ~TriangleBuilder() override = default;

    QString name() const override;
    QPolygonF createPolygon() const override;
};


#endif // TRIANGLE_BUILDER_H
