#pragma once
#ifndef _DE_INITIALIZATION_DOMAIN_UNIFORM_H_
#define _DE_INITIALIZATION_DOMAIN_UNIFORM_H_


#include "InitializationStrategy.h"


namespace de {

	//! \brief Implémentation de la stratégie de sélection qui conserve les individus ayant la meilleure valeur de fitness.
	//!
	//! \details Cette classe est une stratégie d'initialisation spécifique utilisée dans l'algorithme d'évolution différentielle. Elle initialise les individus par une valeur pseudo-aléatoire répartie uniformément sur le domaine du problème.
	class InitializationDomainUniform : public InitializationStrategy
	{
	public:
		InitializationDomainUniform();															//!< Constructeur par défaut.
		InitializationDomainUniform(InitializationDomainUniform const&) = default;				//!< Constructeur de copie.
		InitializationDomainUniform(InitializationDomainUniform&&) = default;					//!< Constructeur de déplacement.
		InitializationDomainUniform& operator=(InitializationDomainUniform const&) = default;	//!< Opérateur d'assignation de copie.
		InitializationDomainUniform& operator=(InitializationDomainUniform&&) = default;		//!< Opérateur d'assignation de déplacement.
		~InitializationDomainUniform() override = default;										//!< Destructeur par défaut.

		void process(SolutionStrategy const& solutionStrategy, Population& actualPopulation) override; //!< Implémentation de la méthode d'initialization où chaque solution est déterminée pseudo-aléatoirement selon une distribtion uniforme du domaine.

		DEFINE_OVERRIDE_CLONE_METHOD(InitializationDomainUniform)	                            //!< Macro définissant automatiquement la substitution de la méthode de clonage.		
	};

}

#endif // _DE_INITIALIZATION_DOMAIN_UNIFORM_H_
