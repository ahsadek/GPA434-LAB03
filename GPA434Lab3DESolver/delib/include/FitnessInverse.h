#pragma once
#ifndef _DE_FITNESS_INVERSE_H_
#define _DE_FITNESS_INVERSE_H_


#include "FitnessStrategy.h"


namespace de {

	//! \brief Stratégie de fitness qui transforme la valeur par inversion.
	//!
	//! \details Cette classe est une implémentation de `FitnessStrategy` 
	//! qui effectue une transformation d'inversion 1.0/value sur la valeur 
	//! donnée. 
	//! Si la valeur est 0, une valeur de substitution est utilisée à la 
	//! place.
	class FitnessInverse : public FitnessStrategy
	{
	public:
		FitnessInverse(double substitution = 0.0);					//!< Constructeur avec valeur de substitution pour l'inversion.
		FitnessInverse(FitnessInverse const&) = default;			//!< Constructeur de copie.
		FitnessInverse(FitnessInverse&&) = default;					//!< Constructeur de déplacement.
		FitnessInverse& operator=(FitnessInverse const&) = default; //!< Opérateur d'assignation de copie.
		FitnessInverse& operator=(FitnessInverse&&) = default;      //!< Opérateur d'assignation de déplacement.
		~FitnessInverse() override = default;                       //!< Destructeur.

		double substitution() const;								//!< Retourne la valeur de substitution.
		void setSubstitution(double substitution);					//!< Définit la valeur de substitution.

		double process(double value) override;						//!< Applique la transformation d'inversion à la valeur donnée.

		DEFINE_OVERRIDE_CLONE_METHOD(FitnessInverse)	            //!< Macro définissant automatiquement la substitution de la méthode de clonage.		

	private:
		double mSubstitution{};										//!< Valeur de substitution utilisée si la valeur à inverser est 0.
	};


}


#endif // _DE_FITNESS_INVERSE_H_
