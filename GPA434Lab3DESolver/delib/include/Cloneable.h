#pragma once
#ifndef _CLONEABLE_H_
#define _CLONEABLE_H_



//! \brief Déclare une méthode de clonage abstraite dans une classe.
//! \details Cette macro définit une méthode abstraite 'clone' dans la classe.
//! Cette méthode, lorsqu'implémentée dans les sous-classes, doit retourner un clone
//! de l'instance de l'objet.C'est une méthode purement virtuelle, ce qui rend
//! la classe abstraite si aucune autre méthode de clonage n'est fournie.
//! \param className Le nom de la classe pour laquelle la méthode abstraite 'clone' est déclarée.
#define DEFINE_ABSTRACT_CLONE_METHOD(className) \
    virtual className* clone() const = 0;


//! \brief Implémente une méthode de clonage pour la classe.
//! \details Cette macro crée une implémentation concrète de la méthode 'clone'
//!          pour une classe donnée.Elle retourne une nouvelle instance de la 
//!          classe, créée par copie.
//! \param className Le nom de la classe pour laquelle la méthode 'clone' est implémentée.
//! \return Un pointeur vers le nouvel objet cloné.
#define DEFINE_OVERRIDE_CLONE_METHOD(className) \
    className* clone() const override {         \
        return new className(*this);            \
    }




#endif // _CLONEABLE_H_