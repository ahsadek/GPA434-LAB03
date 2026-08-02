#pragma once
#ifndef _DE_ADAPTIVE_DOMAIN_NO_CONSTRAINT_H_
#define _DE_ADAPTIVE_DOMAIN_NO_CONSTRAINT_H_


#include "AdaptiveDomainStrategy.h"


namespace de {

	//! \class AdaptiveDomainNoConstraint
	//!
	//! \brief Stratégie de domaine adaptatif sans contraintes pour l'évolution différentielle.
	//!
	//! \details Cette classe est une spécialisation de la stratégie de domaine adaptatif qui 
	//! n'impose pas de contraintes supplémentaires sur le domaine des solutions pendant leur 
	//! évolution. Elle sert à adapter les individus de la population dans l'algorithme d'évolution 
	//! différentielle sans restreindre leur espace de recherche. Cela peut être utile dans des scénarios 
	//! où la liberté totale est accordée aux solutions pour explorer l'espace de recherche, même 
	//! au-delà du domaine initialement proposé.
	//! 
	//! Cette stratégie ne fait rien de particulier, elle se contente de laisser les solutions évoluer.
	//! 
	//! Cette stratégie est utilisée par défaut dans l'algorithme d'évolution différentielle.
	class AdaptiveDomainNoConstraint : public AdaptiveDomainStrategy
	{
	public:
		//! \brief Constructeur par défaut.
		//! \details Initialise une nouvelle instance de AdaptiveDomainNoConstraint.
		AdaptiveDomainNoConstraint();

		//! \brief Implémentation de la stratégie.
		//! \details Sans contrainte, permet une exploration complète de l'espace de solutions.
		//! \param solutionDomain Le domaine de solution actuel.
		//! \param actualPopulation La population à initialiser.
		void process(SolutionDomain const& solutionDomain, Population& actualPopulation) override; 
		//!
		//! \brief Substitution de la fonction de clonage.
		//! \return Un nouveau clone de l'objet courant.
		DEFINE_OVERRIDE_CLONE_METHOD(AdaptiveDomainNoConstraint)
	};

}


#endif // _DE_ADAPTIVE_DOMAIN_NO_CONSTRAINT_H_