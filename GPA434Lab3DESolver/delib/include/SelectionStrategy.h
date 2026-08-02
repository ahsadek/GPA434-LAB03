#pragma once
#ifndef _DE_SELECTION_STRATEGY_H_
#define _DE_SELECTION_STRATEGY_H_


#include <string>
#include "Strategy.h"


namespace de {


	class Population;
	class OptimizationStrategy;


	//! \brief Stratégie de sélection pour l'évolution différentielle.
	//!
	//! \details Cette classe est la base pour toutes les stratégies de sélection, qui sont utilisées pour déterminer les individus à conserver dans l'algorithme d'évolution différentielle.
	class SelectionStrategy : public Strategy
	{
	public:
		SelectionStrategy(std::string const& name, std::string const& summary, std::string const& description);//!< Constructeur.
		SelectionStrategy(SelectionStrategy const&) = default;						//!< Constructeur de copie.
		SelectionStrategy(SelectionStrategy&&) = default;							//!< Constructeur de déplacement.
		SelectionStrategy& operator=(SelectionStrategy const&) = default;			//!< Opérateur d'assignation de copie.
		SelectionStrategy& operator=(SelectionStrategy&&) = default;				//!< Opérateur d'assignation de déplacement.
		~SelectionStrategy() override = default;										//!< Destructeur virtuel.

		virtual void prepare([[maybe_unused]] Population const& actualPopulation);	//!< Prépare la population pour la sélection. Par défaut, ne fait rien.

		virtual void process(OptimizationStrategy const& optStrategy, Population& actualPopulation, Population const & trialPopulation) = 0; //!< Sélectionne les individus à conserver dans la population. Méthode virtuelle pure qui doit être redéfinie dans les classes dérivées.
	};

}


#endif // _DE_SELECTION_STRATEGY_H_
