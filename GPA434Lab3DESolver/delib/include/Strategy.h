#pragma once
#ifndef _DE_STRATEGY_H_
#define _DE_STRATEGY_H_


#include <string>
#include "Cloneable.h"


namespace de {


    //! \class Strategy
    //! 
    //! \brief La classe de base pour les stratégies dans l'algorithme d'évolution différentielle.
    //! 
    //! \details Cette classe fournit une interface commune pour toutes les stratégies
    //! utilisées dans l'algorithme d'évolution différentielle. Elle contient des informations
    //! de base comme le nom, le résumé et la description de la stratégie.
    class Strategy
    {
    public:
        //! \brief Constructeur de Strategy.
        //! \param name Le nom de la stratégie.
        //! \param summary Le résumé de la stratégie.
        //! \param description La description détaillée de la stratégie.
        //! 
        //! \details Ce constructeur initialise la stratégie avec les informations fournies.
        Strategy(std::string const& name, std::string const& summary, std::string const& description);
        //! \brief Constructeur de copie.
        Strategy(Strategy const&) = default;
        //! \brief Constructeur de déplacement.
        Strategy(Strategy&&) = default;
        //! \brief Opérateur d'assignation de copie.
        Strategy& operator=(Strategy const&) = default;
        //! \brief Opérateur d'assignation de déplacement.
        Strategy& operator=(Strategy&&) = default;
        //! \brief Destructeur virtuel.
        virtual ~Strategy() = default;
        //!
        //! \brief Accesseur retournant le nom de la stratégie.
        //! \details Cette méthode renvoie le nom attribué à la stratégie.
        //! \return Le nom de la stratégie.
        std::string name() const;
        //!
        //! \brief Accesseur retournant le résumé de la stratégie.
        //! \return Le résumé de la stratégie. 
        //! \details Cette méthode renvoie le résumé de la stratégie.
        std::string summary() const;
        //! 
        //! \brief Accesseur retournant la description de la stratégie.
        //! \details Cette méthode renvoie la description détaillée de la stratégie.
        //! \return La description de la stratégie.
        std::string description() const;
        //!
        //! \brief Méthode abstraite permettant le clonage de l'objet.
        //! \details Cette méthode est une méthode abstraite qui doit être implémentée
        //! dans les sous-classes pour permettre la duplication de stratégies.
        //! \return Un nouveau clone de l'objet Strategy.
        DEFINE_ABSTRACT_CLONE_METHOD(Strategy)

    private:
        std::string mName;
        std::string mSummary;
        std::string mDescription;
    };

}


#endif // _DE_STRATEGY_H_