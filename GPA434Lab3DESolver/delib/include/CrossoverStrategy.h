#pragma once
#ifndef _DE_CROSSOVER_STRATEGY_H_
#define _DE_CROSSOVER_STRATEGY_H_


#include <string>
#include <random>
#include "Strategy.h"


namespace de {

	class Population;

    //! \brief Stratégie générique pour la fonction de croisement dans un 
    //! algorithme génétique.
    //!
    //! \details Le taux de croisement détermine la probabilité qu'un 
    //! croisement se produise entre deux individus. Cette classe est 
    //! destinée à être héritée pour implémenter des méthodes de croisement 
    //! spécifiques.
    class CrossoverStrategy : public Strategy
    {
    public:
        CrossoverStrategy(std::string const& name, std::string const& summary, std::string const& description, double crossoverRate = 0.75);                      //!< Constructeur avec initialisation du taux de croisement. La valeur est bornée entre 0.0 et 1.0.
        CrossoverStrategy(CrossoverStrategy const&) = default;              //!< Constructeur de copie par défaut.
        CrossoverStrategy(CrossoverStrategy&&) = default;                   //!< Constructeur de déplacement par défaut.
        CrossoverStrategy& operator=(CrossoverStrategy const&) = default;   //!< Opérateur d'assignation de copie par défaut.
        CrossoverStrategy& operator=(CrossoverStrategy&&) = default;        //!< Opérateur d'assignation de déplacement par défaut.
        ~CrossoverStrategy() override = default;                            //!< Destructeur.

        double crossoverRate() const;                                       //!< Retourne le taux de croisement 'R'.
        void setCrossoverRate(double crossoverRate);                        //!< Définit le taux de croisement 'R'. La valeur est bornée entre 0.0 et 1.0.

        virtual void prepare([[maybe_unused]] Population const& trialPopulation);  //!< Prépare l'opération de croisement. Par défaut, ne fait rien.
        virtual void process(Population const& actualPopulation, Population const& mutantPopulation, Population& trialPopulation) = 0; //!< Effectue le croisement. Doit être implémenté par les classes dérivées.

    protected:
        bool isCrossingOver() const;                                        //!< Détermine si un croisement doit avoir lieu en fonction du taux de croisement.
        static std::default_random_engine mRandomGenerator;                 //!< Générateur de nombres aléatoires.

    private:
        mutable std::bernoulli_distribution mBernouilliDistribution;
    };

}


#endif // _DE_CROSSOVER_STRATEGY_H_
