#pragma once
#ifndef _DE_SELECTION_BEST_FITNESS_H_
#define _DE_SELECTION_BEST_FITNESS_H_


#include "SelectionStrategy.h"


namespace de {

	//! \brief Implémentation de la stratégie de sélection qui conserve les individus ayant la meilleure valeur de fitness.
	//!
	//! \details Cette classe est une stratégie de sélection spécifique utilisée dans l'algorithme d'évolution différentielle. Elle sélectionne les individus à conserver dans la population en fonction de leur valeur de fitness. Seuls les individus ayant la meilleure valeur de fitness sont conservés.
	class SelectionBestFitness : public SelectionStrategy
	{
	public:
		//!
		//!
		SelectionBestFitness();													//!< Constructeur par défaut.
		SelectionBestFitness(SelectionBestFitness const&) = default;			//!< Constructeur de copie.
		SelectionBestFitness(SelectionBestFitness&&) = default;					//!< Constructeur de déplacement.
		SelectionBestFitness& operator=(SelectionBestFitness const&) = default; //!< Opérateur d'assignation de copie.
		SelectionBestFitness& operator=(SelectionBestFitness&&) = default;      //!< Opérateur d'assignation de déplacement.
		~SelectionBestFitness() override = default;								//!< Destructeur par défaut.
		//!
		//!
		//! \brief Implémentation de la méthode de sélection basée sur la meilleure valeur de fitness.
		//!
		//! \details Cette méthode est une partie de la stratégie de sélection dans l'algorithme d'évolution
		//! différentielle. Elle sélectionne les individus à conserver dans la population sur la base
		//! de leur valeur de fitness. Seuls les individus avec la meilleure valeur de fitness sont conservés
		//! pour les générations futures.
		//!
		//! \param optStrategy Référence constante à l'objet OptimizationStrategy représentant la stratégie d'optimisation en cours.
		//! \param actualPopulation Référence à l'objet Population représentant la population actuelle.
		//! \param trialPopulation Référence en lecture seule à l'objet représentant la population d'essai.
		void process(OptimizationStrategy const& optStrategy, Population& actualPopulation, Population const & trialPopulation) override; //!< Implémentation de la méthode de sélection qui conserve les individus ayant la meilleure valeur de fitness.
		//!
		//!
		//! \brief Substitution de la fonction de clonage.
		//! \details Cette méthode implémente la fonction de clonage essentielle à la classe Strategy. 
		//! \return Un nouveau clone de l'objet SelectionBestFitness.
		DEFINE_OVERRIDE_CLONE_METHOD(SelectionBestFitness)	                    //!< Macro définissant automatiquement la substitution de la méthode de clonage.
	};

}

#endif // _DE_SELECTION_BEST_FITNESS_H_
