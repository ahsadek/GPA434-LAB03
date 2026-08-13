#pragma once
#ifndef FACE_SHAPE_H
#define FACE_SHAPE_H

// Fichier : FaceShape.h
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/06
// Interface commune aux traits d'un visage échantillonnés en points.

#include <QPolygonF>
#include <QString>


class QPainter;


//! \brief Interface commune aux traits d'un visage.
//! Chaque trait porte un nom, sait produire les points de sa courbe et
//! sait se dessiner lui-même.
class FaceShape
{
public:
    FaceShape(QString const & name);
    FaceShape(FaceShape const &) = default;
    FaceShape& operator=(FaceShape const &) = default;
    virtual ~FaceShape() = default;

    QString name() const;

    virtual QPolygonF samplePoints(int sampleCount) const = 0;
    virtual void draw(QPainter & painter, int sampleCount) const = 0;

private:
    QString mName;
};


#endif // FACE_SHAPE_H
