#pragma once
#ifndef _DE_ADAPTIVE_DOMAIN_STRATEGY_H_
#define _DE_ADAPTIVE_DOMAIN_STRATEGY_H_


#include "Strategy.h"


namespace de
{

	class SolutionDomain;
	class Population;

	//! \class AdaptiveDomainStrategy
	//!
	//! \brief Stratégie de gestion du domaine des solutions pendant l'évolution.
	//!
	//! \details Cette classe représente une stratégie de gestion du domaine des solutions 
	//! 
	//! L'objectif est de permettre de modifier le domaine des solutions pendant l'évolution.
	class AdaptiveDomainStrategy : public Strategy
	{
	public:
		//!
		//! \brief Constructeur par défaut.
		//! \details Initialise une nouvelle instance de la stratégie de domaine adaptatif avec les informations fournies.
		//! \param name Le nom de la stratégie.
		//! \param summary Le résumé de la stratégie.
		//! \param description La description détaillée de la stratégie.
		AdaptiveDomainStrategy(std::string const& name, std::string const& summary, std::string const& description);
		AdaptiveDomainStrategy(AdaptiveDomainStrategy const&) = default;				//!< Constructeur de copie.
		AdaptiveDomainStrategy(AdaptiveDomainStrategy&&) = default;						//!< Constructeur de déplacement.
		AdaptiveDomainStrategy& operator=(AdaptiveDomainStrategy const&) = default;		//!< Opérateur d'assignation de copie.
		AdaptiveDomainStrategy& operator=(AdaptiveDomainStrategy&&) = default;			//!< Opérateur d'assignation de déplacement.
		~AdaptiveDomainStrategy() override = default;									//!< Destructeur virtuel.
		//!
		//! \brief Prépare la population pour l'initialisation.
		//! \details Cette méthode sert à effectuer des opérations préparatoires sur 
		//! la population avant le processus d'initialisation. Par défaut, ne fait rien, 
		//! mais peut être redéfinie dans les classes dérivées pour des besoins spécifiques.
		//! \param actualPopulation La population actuelle à préparer.
		virtual void prepare([[maybe_unused]] Population const& actualPopulation);
		//!
		//! \brief Initialise les individus de la population.
		//! \details Cette méthode permettant l'adaptation des individus de la population 
		//! au sein du domaine de solution. C'est une méthode abstraite devant être 
		//! implémentée dans les classes dérivées pour définir comment les solutions sont 
		//! contraintes et adaptées par le domaine.
		//! \param solutionDomain Le domaine de solution actuel.
		//! \param actualPopulation La population à initialiser.
		virtual void process(SolutionDomain const& solutionDomain, Population& actualPopulation) = 0; //!< Initialise les individus de la population. Méthode virtuelle pure qui doit être redéfinie dans les classes dérivées.
	};

}


#endif // _DE_ADAPTIVE_DOMAIN_STRATEGY_H_