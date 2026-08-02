#pragma once
#ifndef _DE_PEAK_FUNCTION_MAX_SOLUTION_H_
#define _DE_PEAK_FUNCTION_MAX_SOLUTION_H_


#include "PeakFunctionSolution.h"


namespace de {


	//! \class PeakFunctionMaxSolution
	//!
	//! \brief Classe représentant une stratégie de solution pour la résolution 
	//! du maximum absolu de la fonction 'peak' de Matlab.
	//!
	//! \details Cette classe est une spécialisation de `PeakFunctionSolution` axée spécifiquement
	//! sur la recherche du maximum absolu de la fonction 'peak'. Elle utilise les caractéristiques
	//! et les méthodes de `PeakFunctionSolution` tout en les adaptant pour se concentrer sur la 
	//! découverte et l'optimisation des valeurs maximales de la fonction.
	class PeakFunctionMaxSolution : public PeakFunctionSolution
	{
	public:
		//!
		PeakFunctionMaxSolution();														//!< Constructeur par défaut.
		PeakFunctionMaxSolution(PeakFunctionMaxSolution const &) = default;				//!< Constructeur de copie.
		PeakFunctionMaxSolution(PeakFunctionMaxSolution &&) = default;					//!< Constructeur de déplacement.
		PeakFunctionMaxSolution& operator=(PeakFunctionMaxSolution const &) = default;	//!< Opérateur d'assignation de copie.
		PeakFunctionMaxSolution& operator=(PeakFunctionMaxSolution &&) = default;		//!< Opérateur d'assignation de déplacement.
		~PeakFunctionMaxSolution() override = default;									//!< Destructeur.
		//!
		//! \brief Retourne une représentation textuelle de la solution.
		//! \param solution La solution à représenter.
		//! \returns Une chaîne de caractères représentant la solution.
		std::string toString(de::Solution const & solution) const override;				//!< Retourne une représentation textuelle de la solution.
		//!
		//! \brief Substitution de la fonction de clonage.
		//! \return Un nouveau clone de l'objet courant.
		DEFINE_OVERRIDE_CLONE_METHOD(PeakFunctionMaxSolution)

	protected:
		//!
		//! \brief Effectue le traitement nécessaire pour obtenir la valeur maximale.
		//! \param solution La solution à évaluer.
		//! \returns Le score de performance de la solution, indiquant sa proximité au maximum absolu.
		double process(de::Solution const & solution) override;
	};

} // namespace de


#endif // _DE_PEAK_FUNCTION_MAX_SOLUTION_H_
