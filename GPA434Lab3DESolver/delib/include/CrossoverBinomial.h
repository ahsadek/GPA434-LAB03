#pragma once
#ifndef _DE_CROSSOVER_BINOMIAL_H_
#define _DE_CROSSOVER_BINOMIAL_H_


#include "CrossoverStrategy.h"


namespace de {

	class Population;

	//! \brief Stratégie de croisement binomial pour un algorithme génétique.
	//!
	//! \details Cette classe hérite de CrossoverStrategy et implémente une 
	//! méthode spécifique de croisement, appelée croisement binomial. Le 
	//! croisement binomial est une étape où chaque élément d'un vecteur cible 
	//! est comparé à un vecteur mutant correspondant. Pour chaque élément, un 
	//! tirage aléatoire décide s'il est conservé du vecteur cible ou remplacé 
	//! par celui du vecteur mutant, créant ainsi un nouveau vecteur "trial". 
	class CrossoverBinomial : public CrossoverStrategy
	{
	public:
		CrossoverBinomial(double Cr = 0.75);								//!< Constructeur avec initialisation du taux de croisement.
		CrossoverBinomial(CrossoverBinomial const&) = default;				//!< Constructeur de copie par défaut.
		CrossoverBinomial(CrossoverBinomial&&) = default;					//!< Constructeur de déplacement par défaut.
		CrossoverBinomial& operator=(CrossoverBinomial const&) = default;	//!< Opérateur d'assignation de copie par défaut.
		CrossoverBinomial& operator=(CrossoverBinomial&&) = default;		//!< Opérateur d'assignation de déplacement par défaut.
		~CrossoverBinomial() override = default;							//!< Destructeur.

		void prepare(Population const& trialPopulation) override;			//!< Prépare l'opération de croisement. Override la méthode de la classe parente.
		void process(Population const& actualPopulation, Population const& mutantPopulation, Population& trialPopulation)  override; //!< Effectue le croisement binomial.

		DEFINE_OVERRIDE_CLONE_METHOD(CrossoverBinomial)	                    //!< Macro définissant automatiquement la substitution de la méthode de clonage.
	private:
		std::uniform_int_distribution<size_t> mSolutionPositionDistribution;
	};

}


#endif // _DE_CROSSOVER_BINOMIAL_H_
