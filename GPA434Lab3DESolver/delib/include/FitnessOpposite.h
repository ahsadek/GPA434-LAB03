#pragma once
#ifndef _DE_FITNESS_OPPOSITE_H_
#define _DE_FITNESS_OPPOSITE_H_


#include "FitnessStrategy.h"


namespace de {

	//! \brief Stratégie de fitness qui renvoie l'opposé de la valeur donnée.
	//!
	//! \details Cette classe est une implémentation de la classe 
	//! `FitnessStrategy` qui retourne l'opposé de la valeur donnée.
	class FitnessOpposite : public FitnessStrategy
	{
	public:
		FitnessOpposite();												//!< Constructeur par défaut.
		FitnessOpposite(FitnessOpposite const&) = default;				//!< Constructeur de copie.
		FitnessOpposite(FitnessOpposite&&) = default;					//!< Constructeur de déplacement.
		FitnessOpposite& operator=(FitnessOpposite const&) = default;	//!< Opérateur d'assignation de copie.
		FitnessOpposite& operator=(FitnessOpposite&&) = default;		//!< Opérateur d'assignation de déplacement.
		~FitnessOpposite() override = default;                          //!< Destructeur.

		double process(double value) override;							//!< Traite la valeur de fitness en retournant son opposé.

		DEFINE_OVERRIDE_CLONE_METHOD(FitnessOpposite)					//!< Macro définissant automatiquement la substitution de la méthode de clonage.		
	};


}


#endif // _DE_FITNESS_OPPOSITE_H_
