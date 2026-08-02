#pragma once
#ifndef _DE_INITIALIZATION_BY_SOLUTION_H_
#define _DE_INITIALIZATION_BY_SOLUTION_H_


#include "InitializationStrategy.h"


namespace de {

	//! \brief Implémentation de la stratégie de sélection qui conserve les individus ayant la meilleure valeur de fitness.
	//!
	//! \details Cette classe est une stratégie d'initialisation spécifique utilisée dans l'algorithme d'évolution différentielle. Elle initialise les individus par une valeur pseudo-aléatoire répartie uniformément sur le domaine du problème.
	class InitializationBySolution : public InitializationStrategy
	{
	public:
		InitializationBySolution();														//!< Constructeur par défaut.
		InitializationBySolution(InitializationBySolution const&) = default;			//!< Constructeur de copie.
		InitializationBySolution(InitializationBySolution&&) = default;					//!< Constructeur de déplacement.
		InitializationBySolution& operator=(InitializationBySolution const&) = default;	//!< Opérateur d'assignation de copie.
		InitializationBySolution& operator=(InitializationBySolution&&) = default;		//!< Opérateur d'assignation de déplacement.
		~InitializationBySolution() override = default;									//!< Destructeur par défaut.

		void process(SolutionStrategy const& solutionStrategy, Population& actualPopulation) override; //!< Implémentation de la méthode d'initialization où chaque solution est déterminée pseudo-aléatoirement selon une distribtion uniforme du domaine.

		DEFINE_OVERRIDE_CLONE_METHOD(InitializationBySolution)							//!< Macro définissant automatiquement la substitution de la méthode de clonage.		
	};

}

#endif // _DE_INITIALIZATION_BY_SOLUTION_H_
