#pragma once
#ifndef POLYGON_BUILDER_H
#define POLYGON_BUILDER_H

// Fichier : PolygonBuilder.h
// GPA434 - Laboratoire 3
// Création : Équipe GPA434, 2026/08/02
// Interface commune pour la création polymorphique des polygones.

#include <QPolygonF>
#include <QString>


//! \brief Interface commune aux classes qui construisent une forme normalisée.
class PolygonBuilder
{
public:
    PolygonBuilder() = default;
    PolygonBuilder(PolygonBuilder const &) = default;
    PolygonBuilder& operator=(PolygonBuilder const &) = default;
    virtual ~PolygonBuilder();

    virtual QString name() const = 0;
    virtual QPolygonF createPolygon() const = 0;
};


#endif // POLYGON_BUILDER_H
