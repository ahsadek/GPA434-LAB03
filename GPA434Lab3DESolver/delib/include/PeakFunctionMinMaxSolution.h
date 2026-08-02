#pragma once
#ifndef _DE_PEAK_FUNCTION_MIN_MAX_SOLUTION_H_
#define _DE_PEAK_FUNCTION_MIN_MAX_SOLUTION_H_


#include "PeakFunctionSolution.h"


namespace de {

	//! \brief Classe représentant une stratégie de solution pour la 
	//! résolution des optimaux absolus de la fonction 'peak' de Matlab 
	//! (minimum et maximum absolus).
	//! 
	//! \class PeakFunctionMinMaxSolution
	//!
	//! \brief Classe représentant une stratégie de solution pour la résolution 
	//! des extrema de la fonction 'peak' de Matlab.
	//!
	//! \details Cette classe est une spécialisation de `PeakFunctionSolution` axée spécifiquement
	//! sur la recherche du minimum et du maximum absolu de la fonction 'peak'. Elle utilise 
	//! les caractéristiques et les méthodes de `PeakFunctionSolution` tout en les adaptant pour 
	//! se concentrer sur la découverte et l'optimisation des valeurs minimales et maximales de la fonction.
	class PeakFunctionMinMaxSolution : public PeakFunctionSolution
	{
	public:
		//!
		PeakFunctionMinMaxSolution();															//!< Constructeur par défaut.
		PeakFunctionMinMaxSolution(PeakFunctionMinMaxSolution const &) = default;				//!< Constructeur de copie.
		PeakFunctionMinMaxSolution(PeakFunctionMinMaxSolution &&) = default;					//!< Constructeur de déplacement.
		PeakFunctionMinMaxSolution& operator=(PeakFunctionMinMaxSolution const &) = default;	//!< Opérateur d'assignation de copie.
		PeakFunctionMinMaxSolution& operator=(PeakFunctionMinMaxSolution &&) = default;			//!< Opérateur d'assignation de déplacement.
		~PeakFunctionMinMaxSolution() override = default;										//!< Destructeur.
		//!
		//! \brief Retourne une représentation textuelle de la solution.
		//! \param solution La solution à représenter.
		//! \returns Une chaîne de caractères représentant la solution.
		std::string toString(de::Solution const & solution) const override;

		EngineParameters engineParameters() const override;                            //!< Retourne les paramètres du moteur adaptés à cette problématique.

		//!
		//! \brief Substitution de la fonction de clonage.
		//! \return Un nouveau clone de l'objet courant.
		DEFINE_OVERRIDE_CLONE_METHOD(PeakFunctionMinMaxSolution)

	protected:
		//!
		//! \brief Effectue le traitement nécessaire pour obtenir les valeurs minimale et maximale.
		//! \param solution La solution à évaluer.
		//! \returns Le score de performance de la solution, indiquant sa proximité au minimum et au maximum absolu.
		double process(de::Solution const & solution) override;									//!< Effectue le traitement nécessaire pour obtenir la solution optimale.
	};

} // namespace de


#endif // _DE_PEAK_FUNCTION_MIN_MAX_SOLUTION_H_
