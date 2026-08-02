#pragma once
#ifndef _DE_SOLUTION_STRATEGY_H_
#define _DE_SOLUTION_STRATEGY_H_


#include <memory>
#include "Strategy.h"
#include "SolutionDomain.h"
#include "EngineParameters.h"
#include "OptimizationStrategy.h"
#include "FitnessStrategy.h"


namespace de {

	class Population;
	class Solution;
	

	//! \class SolutionStrategy
	//!
	//! \brief Stratégie de la solution pour l'évolution différentielle.
	//!
	//! \details Cette classe est l'une des plus importante de toute la librairie `delib`. Elle permet la définition du problème à résoudre.
	//! Elle permet de définir toutes les caractéristiques nécessaires à l'engin d'évolution différentielle pour résoudre un problème.
	//! 
	//! Elle hérite de la classe Strategy et défini une interface spécifique pour une intégration cohérente dans l'architecture globale de l'algorithme.
	//! 
	//! Plus spécifiquement, ...	
	class SolutionStrategy : public Strategy
	{
	public:
		//! \brief Constructeur.
		//! \param name Le nom de la stratégie.
		//! \param summary Le résumé de la stratégie.
		//! \param description La description détaillée de la stratégie.
		//! \details Ce constructeur initialise la stratégie de solution avec les informations fournies.
		SolutionStrategy(std::string const& name, std::string const& summary, std::string const& description);
		//!
		//! \brief Constructeur de copie.
		//! \param other Une autre instance de SolutionStrategy à copier.
		SolutionStrategy(SolutionStrategy const& other);
		//!
		//! \brief Constructeur de déplacement.
		//! \param other Une autre instance de SolutionStrategy à déplacer.		
		SolutionStrategy(SolutionStrategy&& other);
		//!
		//! \brief Opérateur d'assignation de copie est supprimé.
		SolutionStrategy& operator=(SolutionStrategy const&) = delete;
		//!
		//! \brief Opérateur d'assignation de déplacement est supprimé.
		SolutionStrategy& operator=(SolutionStrategy&&) = delete;
		//!
		//! \brief Destructeur virtuel par défaut.
		~SolutionStrategy() override = default;
		//!
		//! \brief Vérifie si la stratégie de solution est prête à être utilisée.
		//! \details Cette méthode vérifie si la stratégie de solution est prête 
		//! à être utilisée. Elle vérifie si :
		//! - le domaine de la solution est valide (au moins une dimension)
		//! - si la stratégie d'optimisation est définie
		//! - si la stratégie de fitness est définie
		//! - si la fonction validateReadyness() retourne vrai
		//! \returns Vrai si la stratégie est prête, faux sinon.
		bool isReady() const;
		//!
		//! \brief Accesseur retournant le domaine de la solution.
		//! \returns Le domaine de la solution.
		SolutionDomain const& domain() const;	
		//!
		//! \brief Convertit une solution en chaîne de caractères.
		//! \details Méthode abstraite (virtuelle pure) qui doit être redéfinie dans 
		//! les classes dérivées.
		//! \param solution La solution à convertir.
		//! \returns Une représentation sous forme de chaîne de la solution.
		virtual std::string toString(de::Solution const& solution) const = 0;
        //!
		//! \brief Accesseur retournant les paramètres de l'engin d'évolution.
		//! \details Cette méthode retourne les paramètres de l'engin d'évolution 
		//! adaptés au problème à résoudre. Par défaut, la méthode retourne des 
		//! paramètres par défaut. Idéalement, il convient de retourner des 
		//! paramètres pertinents pour le problème.
		//! \returns Les paramètres de l'engin d'évolution.
		virtual EngineParameters engineParameters() const;
		//!
		//! \brief Initialise la population aléatoirement.
		//! \details Cette méthode initialise la population aléatoirement. Elle 
		//! utilise la surcharge de la méthode initializeRandomly(Solution& 
		//! solution) pour initialiser chaque solution de la population.
		//! Si pertinent, il est possible de redéfinir cette méthode afin de 
		//! mieux initialiser la population initiale.
		//! \param actualPopulation La population à initialiser.
		virtual void initializeRandomly(Population& actualPopulation) const;

	protected:
		//!
		//! \brief Domaine de la solution.
		//! \details Le domaine doit être défini par les classes dérivées.
		SolutionDomain mSolutionDomain;
		//!
		//! \brief Vérifie si la stratégie de solution est prête à être utilisée.
		//! \details Il est attendu que cette méthode soit redéfinie dans les classes 
		//! dérivées pour valider si la classe enfant est prête pour ses propres 
		//! éléments internes. Par défaut, retourne vrai.
		//! \returns Vrai si la stratégie est prête pour ses éléments internes, faux sinon.
		virtual bool validateReadyness() const;
		//!
		//! \brief Prépare la population pour l'évaluation.
		//! \details Par défaut, ne fait rien. Peut être redéfinie dans les classes 
		//! dérivées pour effectuer des opérations préparatoires.
		//! Cette fonction est appelée une seule fois au début de la simulation.
		//! \param population La population à préparer.
		virtual void prepare([[maybe_unused]] Population const& population);
		//!
		//! \brief Cette méthode évalue une solution et lui attribut une évaluation 
		//! de performance : **fonction objective**.
		//! 
		//! \details Cette méthode est fondamentale dans l'algorithme d'évolution 
		//! différentielle, car elle implémente la fonction objective.
		//! 
		//! Elle prend une solution en entrée et retourne un score de performance qui 
		//! est essentiel pour guider le processus d'évolution.
		//! 
		//! La méthode `process` doit être redéfinie dans chaque classe dérivée de 
		//! `SolutionStrategy`, fournissant ainsi une mesure spécifique de performance
		//! adaptée au problème à résoudre. La qualité de cette implémentation affecte 
		//! directement l'efficacité de l'algorithme dans la recherche de solutions optimales.
		//! 
		//! \param solution La solution à évaluer.
		//! 
		//! \returns La valeur d'évaluation (fitness) de la solution.
		virtual double process(Solution const& solution) = 0;

		//! \brief Initialise une solution aléatoirement.
		//! \details Cette méthode doit initialiser une solution aléatoirement. 
		//! L'implémentation de base génère une solution aléatoire uniformément répartie 
		//! dans le domaine. Il est poertinent de redéfinir cette méthode si on désire 
		//! initialiser une solution selon une stratégie particulière.
		//! \param solution La solution à initialiser.
		virtual void initializeRandomly(Solution& solution) const;

		//!
		//! \brief Définit la stratégie d'optimisation à utiliser.
		//! \details Détermine la stratégie de maximisation à utiliser. Par défaut, la maximisation est utilisée.
		//! \param strategy Un pointeur vers la stratégie d'optimisation.
		void setOptimizationStrategy(OptimizationStrategy* strategy);
		//!
		//! \brief Définit la stratégie de fitness à utiliser.
		//! \details Détermine la fitness à utiliser. Par défait, la fitness identité est utilisée.
		//! \param strategy Un pointeur vers la stratégie de fitness.
		void setFitnessStrategy(FitnessStrategy* strategy);

	private:
		std::unique_ptr<OptimizationStrategy> mOptimizationStrategy;
		std::unique_ptr<FitnessStrategy> mFitnessStrategy;

		friend class DifferentialEvolution; // Cette classe est amie de DifferentialEvolution, elle peut donc accéder à ses membres privés.
	};

} // namespace de


#endif // _DE_SOLUTION_STRATEGY_H_
