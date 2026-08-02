#pragma once
#ifndef _DE_MUTATION_STRATEGY_H_
#define _DE_MUTATION_STRATEGY_H_


#include <vector>
#include <random>
#include <string>
#include "Strategy.h"


namespace de {

	class Population;
	class Solution;

	//! \brief Interface de base pour une stratégie de mutation.
	//!
	//! \details Cette classe sert de base pour différentes stratégies de 
	//! mutation. 
	//! 
	//! Elle défini des méthodes de préparation et de traitement qui 
	//! seront implémentées par des classes dérivées.
	class MutationStrategy : public Strategy
	{
	public:
		MutationStrategy(std::string const& name, std::string const& summary, std::string const& description, double f = 0.5);									//!< Constructeur par défaut.
		MutationStrategy(MutationStrategy const&) = default;				//!< Constructeur de copie par défaut.
		MutationStrategy(MutationStrategy&&) = default;						//!< Constructeur de déplacement par défaut.
		MutationStrategy& operator=(MutationStrategy const&) = default;		//!< Opérateur d'assignation de copie par défaut.
		MutationStrategy& operator=(MutationStrategy&&) = default;			//!< Opérateur d'assignation de déplacement par défaut.
		~MutationStrategy() override = default;								//!< Destructeur.

		double mutationFactor() const;										//!< Retourne la valeur actuelle du facteur de mutation 'f'.
		void setMutationFactor(double f);									//!< Définit la valeur du facteur de mutation 'f'. La valeur est bornée entre 0.0 et 2.0.

		virtual void prepare(Population const& actual_population, Population& mutant_population); //!< Prépare la population pour la mutation.
		virtual void process(Population const& actual_population, Population& mutant_population) = 0; //!< Applique la stratégie de mutation sur la population.

	protected:
		using ProxySolution = std::vector<Solution const*>;
		ProxySolution mSamples;

		void setupSamples(Population const & source, size_t sample_count);	//!< Prépare un échantillon de solutions à partir de la population source.
		void processSamples(size_t exclusion_index);						//!< Processus de mutation sur un ensemble de solutions (excluant l'indice donné).
		void processSamplesWithoutBest(size_t exclusion_index);				//!< Processus de mutation sur un ensemble de solutions (excluant l'indice donné) sans prendre en compte la meilleure solution.

	private:
		ProxySolution mSolutionProxySample;
		static std::default_random_engine mRandomGenerator;

	private:
		double mF{};
	};

}


#endif // _DE_MUTATION_STRATEGY_H_
