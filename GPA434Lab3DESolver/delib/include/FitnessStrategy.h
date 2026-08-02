#pragma once
#ifndef _DE_FITNESS_STRATEGY_H_
#define _DE_FITNESS_STRATEGY_H_


#include "Strategy.h"


namespace de {

	class Population;

	//! \brief Classe de base pour les stratégies de fitness.
	//!
	//! \details Cette classe est la classe de base pour les différentes 
	//! stratégies de fitness utilisées dans l'algorithme d'évolution 
	//! différentielle. Elle fournit les méthodes de base que chaque 
	//! stratégie de fitness doit implémenter.
	class FitnessStrategy : public Strategy
	{
	public:
		FitnessStrategy(std::string const& name, std::string const& summary, std::string const& description);//!< Constructeur par défaut.
		FitnessStrategy(FitnessStrategy const&) = default;				//!< Constructeur de copie.
		FitnessStrategy(FitnessStrategy&&) = default;					//!< Constructeur de déplacement.
		FitnessStrategy& operator=(FitnessStrategy const&) = default;	//!< Opérateur d'assignation de copie.
		FitnessStrategy& operator=(FitnessStrategy&&) = default;		//!< Opérateur d'assignation de déplacement.
		~FitnessStrategy() override = default;							//!< Destructeur virtuel.

		virtual void prepare([[maybe_unused]] Population const& population); //!< Préparation de la stratégie de fitness. Peut être surchargée par des sous-classes.
		virtual double process(double value) = 0;                       //!< Méthode abstraite pour le traitement de la valeur de fitness. Doit être implémentée par les sous-classes.
	};

}



#endif // _DE_FITNESS_STRATEGY_H_
