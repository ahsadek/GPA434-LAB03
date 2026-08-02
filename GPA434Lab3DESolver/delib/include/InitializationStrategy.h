#pragma once
#ifndef _DE_INITIALIZATION_STRATEGY_H_
#define _DE_INITIALIZATION_STRATEGY_H_


#include <string>
#include "Strategy.h"


namespace de {


	class SolutionStrategy;
	class Population;


	//! \brief Stratégie d'initialisation pour l'évolution différentielle.
	//!
	//! \details Cette classe est la base pour toutes les stratégies d'initialisation, qui sont utilisées pour assigner la valeur nominal des individus lors du démarrage d'une nouvelle simulation de l'évolution différentielle.
	class InitializationStrategy : public Strategy
	{
	public:
		InitializationStrategy(std::string const& name, std::string const& summary, std::string const& description);												//!< Constructeur par défaut.
		InitializationStrategy(InitializationStrategy const&) = default;				//!< Constructeur de copie.
		InitializationStrategy(InitializationStrategy&&) = default;						//!< Constructeur de déplacement.
		InitializationStrategy& operator=(InitializationStrategy const&) = default;		//!< Opérateur d'assignation de copie.
		InitializationStrategy& operator=(InitializationStrategy&&) = default;			//!< Opérateur d'assignation de déplacement.
		~InitializationStrategy() override = default;									//!< Destructeur virtuel.

		virtual void prepare([[maybe_unused]] Population const& actualPopulation);		//!< Prépare la population pour l'initialization. Par défaut, ne fait rien.

		virtual void process(SolutionStrategy const& solutionStrategy, Population& actualPopulation) = 0; //!< Initialise les individus de la population. Méthode virtuelle pure qui doit être redéfinie dans les classes dérivées.
	};

}


#endif // _DE_INITIALIZATION_STRATEGY_H_
