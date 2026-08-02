#pragma once
#ifndef _DE_MUTATION_BEST_1_H_
#define _DE_MUTATION_BEST_1_H_


#include "MutationStrategy.h"


namespace de {

    //! \brief Stratégie de mutation Best1.
    //!
    //! \details Cette classe représente une stratégie de mutation qui 
    //! utilise la technique "Best1".
    //! 
    //! Cette technique sélectionne le meilleur individu de la population 
    //! et deux individus aléatoires pour créer un mutant.
    //! 
    class MutationBest1 : public MutationStrategy
    {
    public:
        MutationBest1(double f = 0.5);                                    //!< Constructeur avec initialisation du facteur de mutation.
        MutationBest1(MutationBest1 const&) = default;                    //!< Constructeur de copie.
        MutationBest1(MutationBest1&&) = default;                         //!< Constructeur de déplacement.
        MutationBest1& operator=(MutationBest1 const&) = default;         //!< Opérateur d'assignation de copie.
        MutationBest1& operator=(MutationBest1&&) = default;              //!< Opérateur d'assignation de déplacement.
        ~MutationBest1() override = default;                              //!< Destructeur.

        void prepare(Population const& actualPopulation, Population& mutantPopulation) override; //!< Prépare la population pour la mutation.
        void process(Population const& actualPopulation, Population& mutantPopulation) override; //!< Applique la stratégie de mutation sur la population.

        DEFINE_OVERRIDE_CLONE_METHOD(MutationBest1)	                      //!< Macro définissant automatiquement la substitution de la méthode de clonage.		
    };

}


#endif // _DE_mutation_best_1_H_
