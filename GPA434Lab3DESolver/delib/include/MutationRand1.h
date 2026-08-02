#pragma once
#ifndef _DE_MUTATION_RAND_1_H_
#define _DE_MUTATION_RAND_1_H_


#include "MutationStrategy.h"


namespace de {

    //! \brief Stratégie de mutation Rand1.
    //!
    //! \details Cette classe est une stratégie de mutation qui utilise la 
    //! technique "Rand1", c'est-à-dire une valeur aléatoire.
    //! 
    //! Cette technique sélectionne trois individus aléatoires dans la 
    //! population pour créer un mutant.
    //! 
    class MutationRand1 : public MutationStrategy
    {
    public:
        MutationRand1(double f = 0.5);                              //!< Constructeur avec initialisation du facteur de mutation.
        MutationRand1(MutationRand1 const&) = default;              //!< Constructeur de copie.
        MutationRand1(MutationRand1&&) = default;                   //!< Constructeur de déplacement.
        MutationRand1& operator=(MutationRand1 const&) = default;   //!< Opérateur d'assignation de copie.
        MutationRand1& operator=(MutationRand1&&) = default;        //!< Opérateur d'assignation de déplacement.
        ~MutationRand1() override = default;                        //!< Destructeur.

        void prepare(Population const& actualPopulation, Population& mutantPopulation) override; //!< Prépare la population pour la mutation.
        void process(Population const& actualPopulation, Population& mutantPopulation) override; //!< Applique la stratégie de mutation sur la population.


        DEFINE_OVERRIDE_CLONE_METHOD(MutationRand1)	                //!< Macro définissant automatiquement la substitution de la méthode de clonage.		

    };

}


#endif // _DE_MUTATION_RAND_1_H_
