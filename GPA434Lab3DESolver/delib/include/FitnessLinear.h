#pragma once
#ifndef _DE_FITNESS_LINEAR_H_
#define _DE_FITNESS_LINEAR_H_


#include "FitnessStrategy.h"


namespace de {

	//! \brief Stratégie de fitness qui traite la valeur en appliquant une 
	//! transformation linéaire.
	//!
	//! \details Cette classe est une implémentation de la classe 
	//! `FitnessStrategy` qui effectue une transformation linéaire de la 
	//! forme y = ax + b sur la valeur donnée.
	class FitnessLinear : public FitnessStrategy
	{
	public:
		FitnessLinear(double a, double b);							//!< Constructeur avec coefficients pour la transformation linéaire.
		FitnessLinear(FitnessLinear const&) = default;				//!< Constructeur de copie.
		FitnessLinear(FitnessLinear&&) = default;					//!< Constructeur de déplacement.
		FitnessLinear& operator=(FitnessLinear const&) = default;	//!< Opérateur d'assignation de copie.
		FitnessLinear& operator=(FitnessLinear&&) = default;		//!< Opérateur d'assignation de déplacement.
		~FitnessLinear() override = default;						//!< Destructeur.

		double a() const;											//!< Retourne le coefficient 'a' de la transformation linéaire.
		double b() const;											//!< Retourne le coefficient 'b' de la transformation linéaire.
		void set(double a, double b);								//!< Définit les coefficients 'a' et 'b' pour la transformation linéaire.
		void reset();												//!< Réinitialise les coefficients 'a' et 'b' à leurs valeurs par défaut.

		double process(double value) override;						//!< Applique la transformation linéaire à la valeur donnée.

		DEFINE_OVERRIDE_CLONE_METHOD(FitnessLinear)	                //!< Macro définissant automatiquement la substitution de la méthode de clonage.		

	private:
		double mA{ 1.0 }, mB{ 0.0 };								//!< Coefficients 'a' et 'b' de la transformation linéaire.
	};


}


#endif // _DE_FITNESS_LINEAR_H_
