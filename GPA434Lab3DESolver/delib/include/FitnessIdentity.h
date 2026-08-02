#pragma once
#ifndef _DE_FITNESS_IDENTITY_H_
#define _DE_FITNESS_IDENTITY_H_


#include "FitnessStrategy.h"


namespace de {

	//! \brief Stratégie de fitness qui retourne la valeur sans transformation.
	//!
	//! \details Cette classe est une implémentation de `FitnessStrategy` qui 
	//! retourne simplement la valeur d'aptitude reçue sans appliquer aucune 
	//! transformation.
	class FitnessIdentity : public FitnessStrategy
	{
	public:
		FitnessIdentity();												//!< Constructeur par défaut.
		FitnessIdentity(FitnessIdentity const&) = default;				//!< Constructeur de copie.
		FitnessIdentity(FitnessIdentity&&) = default;					//!< Constructeur de déplacement.
		FitnessIdentity& operator=(FitnessIdentity const&) = default;	//!< Opérateur d'assignation de copie.
		FitnessIdentity& operator=(FitnessIdentity&&) = default;		//!< Opérateur d'assignation de déplacement.
		~FitnessIdentity() override = default;							//!< Destructeur.

		double process(double value) override;							//!< Retourne la valeur d'aptitude reçue sans aucune transformation.

		DEFINE_OVERRIDE_CLONE_METHOD(FitnessIdentity)					//!< Macro définissant automatiquement la substitution de la méthode de clonage.		
	};

}


#endif // _DE_FITNESS_IDENTITY_H_
