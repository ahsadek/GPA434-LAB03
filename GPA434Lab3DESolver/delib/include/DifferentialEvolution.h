#pragma once
#ifndef _DE_DIFFERENTIAL_EVOLUTION_H_
#define _DE_DIFFERENTIAL_EVOLUTION_H_


#include <memory>
#include <functional>
#include "EngineParameters.h"
#include "SolutionStrategy.h"
#include "Population.h"
#include "History.h"


namespace de {
	
	//! \brief Implémentation de l'algorithme d'évolution différentielle.
	//!
	//! \details L'évolution différentielle est une méthode d'optimisation 
	//! stochastique qui est utilisée pour optimiser les problèmes d'optimisation 
	//! à objectif unique et multivariable. 
	//! 
	//! Cette implémentation ne permet pas la copie de l'objet 
	//! DifferentialEvolution. Si l'utilisateur tente de copier l'objet, une 
	//! erreur de compilation se produira.
	class DifferentialEvolution
	{
	public:
		enum class SetupState { Success, ErrorInvalidParameters, ErrorNoSolution, ErrorInvalidSolution };

		DifferentialEvolution() = default;									//!< Constructeur par défaut.
		DifferentialEvolution(DifferentialEvolution const&) = delete;		//!< Constructeur de copie supprimé.
		DifferentialEvolution& operator=(DifferentialEvolution const&) = delete; //!< Opérateur d'assignation de copie supprimé.
		~DifferentialEvolution() = default;									//!< Destructeur.

		bool isReady() const;												//!< Vérifie si l'objet est prêt à exécuter le processus.
		size_t currentGeneration() const;									//!< Accesseur retournant la génération actuelle.
		Population const& actualPopulation() const;							//!< Accesseur retournant la population actuelle.
		EngineParameters const& engineParameters() const;					//!< Accesseur retournant les paramètres du moteur.
		SolutionStrategy const& solution() const;							//!< Accesseur retournant la solution actuelle. Cette fonction lance une exception si la solution n'est pas définie.

		void setEngineParameters(EngineParameters const& parameters);		//!< Définit les paramètres du moteur. Si les paramètres ne sont pas valides, ils ne sont pas définis.
		SetupState setup(SolutionStrategy* solutionStrategy);				//!< Configure les paramètres du moteur et la stratégie de solution. Attention, la solution possède ses propres paramètres et écrasera toute définition préalable. Si des modifications de paramètres sont souhaitée sur une solution, ils doivent être fait après la fonction setup.
		void reset();														//!< Réinitialise la simulation à un état initial.

		void processToNextGeneration();										//!< Progresse vers la prochaine génération. Ne fait rien si l'engin n'est pas prêt (isReady) ou si un critère d'arrêt est atteint.
		bool isStoppingCriteriaReached() const;								//!< Vérifie si au moins l'un des critères d'arrêt est atteint.
		void process();														//!< Exécute le processus d'évolution jusqu'à ce qu'une condition d'arrêt soit atteinte.
		void process(std::function<void(size_t)> callback);					//!< Exécute le processus d'évolution jusqu'à ce qu'une condition d'arrêt soit atteinte. Fait l'appel de callback à chaque évolution en passant l'époque de la génération actuelle.

		History const& statisticsHistory() const;							//!< Obtient l'historique des statistiques.
		std::string bestSolutionInfo() const;								//!< Obtient l'information sur la meilleure solution.

	private:
		size_t mCurrentGeneration{};
		EngineParameters mEngineParameters;
		std::unique_ptr<SolutionStrategy> mSolution;
		Population mActualPopulation;
		Population mMutantPopulation;
		Population mTrialPopulation;
		History mHistory;

		void processFitness(Population & population);
		void setup(EngineParameters const& parameters);
	};
}


#endif // _DE_DIFFERENTIAL_EVOLUTION_H_
