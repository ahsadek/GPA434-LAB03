#pragma once
#ifndef _DE_OPTIMIZATION_MINIMIZATION_H_
#define _DE_OPTIMIZATION_MINIMIZATION_H_


#include "OptimizationStrategy.h"


namespace de {

    //! \brief Stratégie d'optimisation par minimisation.
    //!
    //! \details Cette classe hérite de OptimizationStrategy et implémente 
    //! une stratégie d'optimisation visant à minimiser une fonction objectif.
    class OptimizationMinimization : public OptimizationStrategy
    {
    public:
        OptimizationMinimization();                                                     //!< Constructeur par défaut.
        OptimizationMinimization(OptimizationMinimization const&) = default;            //!< Constructeur de copie par défaut.
        OptimizationMinimization(OptimizationMinimization&&) = default;                 //!< Constructeur de déplacement par défaut.
        OptimizationMinimization& operator=(OptimizationMinimization const&) = default; //!< Opérateur d'assignation de copie par défaut.
        OptimizationMinimization& operator=(OptimizationMinimization&&) = default;      //!< Opérateur d'assignation de déplacement par défaut.
        ~OptimizationMinimization() override = default;                                 //!< Destructeur.

        bool compare(double v1, double v2) const override;                              //!< Compare deux valeurs pour déterminer si la première est inférieure à la seconde.

        DEFINE_OVERRIDE_CLONE_METHOD(OptimizationMinimization)	                        //!< Macro définissant automatiquement la substitution de la méthode de clonage.
    };


}


#endif //_DE_OPTIMIZATION_MINIMIZATION_H_