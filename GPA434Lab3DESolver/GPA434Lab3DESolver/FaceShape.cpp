// Fichier : FaceShape.cpp
// GPA434 - Laboratoire 3
// Création : Frederic Tchouanguep, Ahmed Sadek, Paul Ayoub, 2026/08/06
// Définition de l'interface des traits du visage.

#include "FaceShape.h"


FaceShape::FaceShape(QString const & name)
    : mName{ name }
{
}

QString FaceShape::name() const
{
    return mName;
}
