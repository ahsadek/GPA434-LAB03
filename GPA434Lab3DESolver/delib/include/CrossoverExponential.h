#pragma once
#ifndef _DE_CROSSOVER_EXPONENTIAL_H_
#define _DE_CROSSOVER_EXPONENTIAL_H_


#include "CrossoverStrategy.h"


namespace de {

	class Population;

	//! \brief Stratégie de croisement exponentiel pour un algorithme génétique.
	//!
	//! \details Cette classe hérite de CrossoverStrategy et implémente une 
	//! méthode spécifique de croisement, appelée croisement exponentiel. Le 
	//! croisement exponentiel commence par sélectionner un point de départ 
	//! aléatoire dans un vecteur cible et, à partir de là, remplace une séquence 
	//! continue d'éléments avec ceux d'un vecteur mutant correspondant. Le 
	//! processus continue jusqu'à un tirage aléatoire déclare la fin de la 
	//! séquence, produisant ainsi un nouveau vecteur "trial".
	class CrossoverExponential : public CrossoverStrategy
	{
	public:
		CrossoverExponential(double Cr = 0.75);									//!< Constructeur avec initialisation du taux de croisement.
		CrossoverExponential(CrossoverExponential const&) = default;			//!< Constructeur de copie par défaut.
		CrossoverExponential(CrossoverExponential&&) = default;					//!< Constructeur de déplacement par défaut.
		CrossoverExponential& operator=(CrossoverExponential const&) = default; //!< Opérateur d'assignation de copie par défaut.
		CrossoverExponential& operator=(CrossoverExponential&&) = default;      //!< Opérateur d'assignation de déplacement par défaut.
		~CrossoverExponential() override = default;								//!< Destructeur.

		void prepare(Population const& trialPopulation) override;				//!< Prépare l'opération de croisement. Override la méthode de la classe parente.
		void process(Population const& actualPopulation, Population const& mutantPopulation, Population& trialPopulation)  override; //!< Effectue le croisement exponentiel.

		DEFINE_OVERRIDE_CLONE_METHOD(CrossoverExponential)	                    //!< Macro définissant automatiquement la substitution de la méthode de clonage.		

	private:
		std::uniform_int_distribution<size_t> mSolutionFirstDistribution;
		std::geometric_distribution<size_t> mSolutionCountDistribution;
	};

}


#endif // _DE_CROSSOVER_EXPONENTIAL_H_
