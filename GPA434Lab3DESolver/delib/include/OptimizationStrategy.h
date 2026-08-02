#pragma once
#ifndef _DE_OPTIMIZATION_STRATEGY_H_
#define _DE_OPTIMIZATION_STRATEGY_H_


#include "Strategy.h"


namespace de {

    //! \brief Interface de base pour une stratégie d'optimisation.
    //!
    //! \details Cette classe sert de base pour différentes stratégies 
    //! d'optimisation. 
    //! 
    //! C'est une interface qui définit une méthode de comparaison nécessaire 
    //! pour toutes les stratégies d'optimisation.
    class OptimizationStrategy : public Strategy
    {
    public:
        OptimizationStrategy(std::string const& name, std::string const& summary, std::string const& description);                                       //!< Constructeur par défaut.
        OptimizationStrategy(OptimizationStrategy const&) = default;            //!< Constructeur de copie par défaut.
        OptimizationStrategy(OptimizationStrategy&&) = default;                 //!< Constructeur de déplacement par défaut.
        OptimizationStrategy& operator=(OptimizationStrategy const&) = default; //!< Opérateur d'assignation de copie par défaut.
        OptimizationStrategy& operator=(OptimizationStrategy&&) = default;      //!< Opérateur d'assignation de déplacement par défaut.
        ~OptimizationStrategy() override = default;                             //!< Destructeur.

        virtual bool compare(double v1, double v2) const = 0;                   //!< Méthode de comparaison pour évaluer si une solution est meilleure qu'une autre. Est-ce que v1 est meilleure que v2.
    };


}


#endif // _DE_OPTIMIZATION_STRATEGY_H_