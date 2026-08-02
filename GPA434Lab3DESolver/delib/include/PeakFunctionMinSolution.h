#pragma once
#ifndef _DE_PEAK_FUNCTION_MIN_SOLUTION_H_
#define _DE_PEAK_FUNCTION_MIN_SOLUTION_H_


#include "PeakFunctionSolution.h"


namespace de {

	//! \class PeakFunctionMinSolution
	//!
	//! \brief Classe représentant une stratégie de solution pour la résolution 
	//! du minimum absolu de la fonction 'peak' de Matlab.
	//!
	//! \details Cette classe est une spécialisation de `PeakFunctionSolution` axée spécifiquement
	//! sur la recherche du minimum absolu de la fonction 'peak'. Elle utilise les caractéristiques
	//! et les méthodes de `PeakFunctionSolution` tout en les adaptant pour se concentrer sur la 
	//! découverte et l'optimisation des valeurs minimales de la fonction.
	class PeakFunctionMinSolution : public PeakFunctionSolution
	{
	public:
		//!
		PeakFunctionMinSolution();														//!< Constructeur par défaut.
		PeakFunctionMinSolution(PeakFunctionMinSolution const&) = default;				//!< Constructeur de copie.
		PeakFunctionMinSolution(PeakFunctionMinSolution&&) = default;					//!< Constructeur de déplacement.
		PeakFunctionMinSolution& operator=(PeakFunctionMinSolution const&) = default;	//!< Opérateur d'assignation de copie.
		PeakFunctionMinSolution& operator=(PeakFunctionMinSolution&&) = default;		//!< Opérateur d'assignation de déplacement.
		~PeakFunctionMinSolution() override = default;									//!< Destructeur.
		//!
		//! \brief Retourne une représentation textuelle de la solution.
		//! \param solution La solution à représenter.
		//! \returns Une chaîne de caractères représentant la solution.
		std::string toString(de::Solution const& solution) const override;
		//!
		//! \brief Substitution de la fonction de clonage.
		//! \return Un nouveau clone de l'objet courant.
		DEFINE_OVERRIDE_CLONE_METHOD(PeakFunctionMinSolution)

	protected:
		//!
		//! \brief Effectue le traitement nécessaire pour obtenir la valeur minimale.
		//! \param solution La solution à évaluer.
		//! \returns Le score de performance de la solution, indiquant sa proximité au minimum absolu.
		double process(de::Solution const& solution) override;
	};


} // namespace de


#endif // _DE_PEAK_FUNCTION_MIN_SOLUTION_H_