#pragma once
#ifndef _DE_ADAPTIVE_DOMAIN_CLAMPED_H_
#define _DE_ADAPTIVE_DOMAIN_CLAMPED_H_


#include "AdaptiveDomainStrategy.h"


namespace de {

	//! \class AdaptiveDomainClamped
	//!
	//! \brief Stratégie de domaine adaptatif avec contraintes pour l'évolution différentielle.
	//!
	//! \details Cette classe est une spécialisation de la stratégie de domaine adaptatif. Contrairement à 
	//! `AdaptiveDomainNoConstraint`, elle impose des contraintes sur le domaine des solutions pendant leur
	//! évolution. Cette stratégie est conçue pour adapter les individus de la population en les maintenant 
	//! à l'intérieur des limites définies du domaine de solutions. 
	//! 
	//! Elle est utile dans les scénarios où il est nécessaire de limiter l'exploration des solutions à un 
	//! espace prédéfini, afin d'assurer que les solutions restent réalisables ou pertinentes pour le 
	//! problème donné.
	//!
	//! Cette stratégie agit en tronquant les solutions dans son domaine, c'est-à-dire en les ramenant 
	//! aux limites du domaine si elles le dépassent lors de l'évolution.
	class AdaptiveDomainClamped : public AdaptiveDomainStrategy
	{
	public:
		//!
		//! \brief Constructeur par défaut.
		//! \details Initialise une nouvelle instance de AdaptiveDomainClamped.
		AdaptiveDomainClamped();
		//!
		//! \brief Implémentation de la stratégie avec contraintes de troncation.
		//! \details Assure que les solutions restent à l'intérieur des limites du domaine.
		//! \param solutionDomain Le domaine de solution actuel.
		//! \param actualPopulation La population dont les solutions doivent être adaptées.
		void process(SolutionDomain const& solutionDomain, Population& actualPopulation) override; 
		//!
		//! \brief Substitution de la fonction de clonage.
		//! \return Un nouveau clone de l'objet courant.
		DEFINE_OVERRIDE_CLONE_METHOD(AdaptiveDomainClamped) //!< Macro définissant automatiquement la substitution de la méthode de clonage.
	};

}


#endif // _DE_ADAPTIVE_DOMAIN_CLAMPED_H_