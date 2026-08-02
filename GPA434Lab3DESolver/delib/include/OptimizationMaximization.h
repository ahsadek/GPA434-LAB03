#pragma once
#ifndef _DE_OPTIMIZATION_MAXIMIZATION_H_
#define _DE_OPTIMIZATION_MAXIMIZATION_H_


#include "OptimizationStrategy.h"


namespace de {

    //! \brief Stratégie d'optimisation par maximisation.
    //!
    //! \details Cette classe hérite de OptimizationStrategy et implémente 
    //! une stratégie d'optimisation visant à maximiser une fonction objectif.
    class OptimizationMaximization : public OptimizationStrategy
    {
    public:
        OptimizationMaximization();                                                     //!< Constructeur par défaut.
        OptimizationMaximization(OptimizationMaximization const&) = default;            //!< Constructeur de copie par défaut.
        OptimizationMaximization(OptimizationMaximization&&) = default;                 //!< Constructeur de déplacement par défaut.
        OptimizationMaximization& operator=(OptimizationMaximization const&) = default; //!< Opérateur d'assignation de copie par défaut.
        OptimizationMaximization& operator=(OptimizationMaximization&&) = default;      //!< Opérateur d'assignation de déplacement par défaut.
        ~OptimizationMaximization() override = default;                                 //!< Destructeur.

        bool compare(double v1, double v2) const override;                              //!< Compare deux valeurs pour déterminer si la première est supérieure à la seconde.

        DEFINE_OVERRIDE_CLONE_METHOD(OptimizationMaximization)	                        //!< Macro définissant automatiquement la substitution de la méthode de clonage.		
    };


}


#endif //_DE_OPTIMIZATION_MAXIMIZATION_H_