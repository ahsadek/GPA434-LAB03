#pragma once
#ifndef _DE_SOLUTION_H_
#define _DE_SOLUTION_H_


#include <vector>


namespace de {

	class SolutionDomain;

	//! \brief Représente une solution de l'évolution différentielle.
	//!
	//! \details Dans le vocabualire de l'évolution différentielle, une 
	//! solution (ou parfois agents) correspond à une solution candidate, une 
	//! solution potentielle. C'est-à-dire, une hypothèse de solution à la 
	//! problématique donnée. C'est l'un des constituant fondamentaux de 
	//! l'évolution différentielle voir ce document (à faire). 
	//! 
	//! Une solution possède :
	//!  - un ensemble de _n_ valeurs (_n_ > 0) correspondant à la position de la solution candidate dans l'espace de solutions.
	//!  - son résultat objectif
	//!  - son résultat de "fitness"
	//!
	//! Une solution est toujours créée et réinitialisée par un SolutionDomain. 
	//! Ce dernier détermine la taille du problème (la dimension de l'espace de 
	//! solutions) et le domaine des valeurs pour chacune des dimensions.
	//! Les valeurs d'une solution peuvent être manipulées par un 
	//! SolutionDomain via la fonction randomize et plus spécifiquement par la 
	//! classe principale DifferentialEvolution. 
	//!
	//! Lors d'une simulation, la classe DifferentialEvolution s'assure que les 
	//! solutions sont toujours adéquatement définies et gère les tâches 
	//! suivantes :
	//!  -# initialisation
	//!  -# génération aléatoire
	//!  -# mutation - croisement - sélection
	//!  -# calcul des fonctions objective et de "fitness"
	//!  -# calculs statistiques
	//! 
	//! Ainsi, il est facile de consulter une solution pour toutes ses valeurs 
	//! via ses accesseurs :
	//!  - isValid() const
	//!  - size() const
	//!  - operator[](size_t)	
    //!  - at(size_t)
	//!  - objective() const
	//!  - fitness() const
	//!
	//! Dans la mise en opération d'une solution, on utilise cette classe en 
	//! lecture pour connaître les valeurs des meilleures solutions.
	class Solution
	{
	public:
		Solution();											//!< Constructeur par défaut. La solution possède une dimension de 0 (aucun élément) et les valeurs objectives et de "fitness" sont mises à leur valeurs initiales. 
		Solution(SolutionDomain const & domain);			//!< Constructeur avec initialisation par un SolutionDomain. La solution est initialisé de la même façon que la fonction setup.
		Solution(Solution const &) = default;				//!< Constructeur de copie.
		Solution(Solution &&) = default;					//!< Constructeur de déplacement.
		Solution& operator=(Solution const &) = default;	//!< Opérateur d'assignation de copie.
		Solution& operator=(Solution &&) = default;			//!< Opérateur d'assignation de déplacement.
		~Solution() = default;								//!< Destructeur.

		bool isValid() const;								//!< Retourne si une solution est valide. Une solution est considérée valide s'il n'a pas une taille de 0.
		void reset();										//!< Réinitialise les valeurs d'une solution. Cette réinitialisation considère une indétermination du problème à résoudre. Ainsi, il devient tel que défini par le constructeur par défaut.

		void setup(SolutionDomain const & domain);			//!< Initialise ou réinitialise une solution selon la détermination d'un SolutionDomain. Cette fonction ne fait qu'initialiser la taille du vecteur de valeurs. Les valeurs sont mises à zéro sans initialisations aléatoires.
		void randomize(SolutionDomain const & domain);		//!< Si la taille de la solution correspond à la taille de domain, initialise toutes les valeurs de la solution à une valeur aléatoire définie par domain.
		void clamp(SolutionDomain const & domain);			//!< Limite la valeur de la solution dans l'intervalle déterminé par le domaine.

		size_t size() const;								//!< Retourne la taille de la solution (la dimensionnalité du problème).
		double operator[](size_t pos) const;				//!< Retourne la \f$i^e\f$ valeur de la solution. Aucune validation des bornes n'est réalisée.
		double & operator[](size_t pos);					//!< Retourne une référence à la \f$i^e\f$ valeur de la solution. Aucune validation des bornes n'est réalisée.
		double at(size_t pos) const;						//!< Retourne la \f$i^e\f$ valeur de la solution. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur.
		double & at(size_t pos);							//!< Retourne une référence à la \f$i^e\f$ valeur de la solution. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur.

		double objective() const;							//!< Retourne la valeur de la fonction objective. Cette valeur n'est valide que si la classe differential_evolution a été utilisée adéquatement.
		double fitness() const;								//!< Retourne la valeur de la fonction de "fitness". Cette valeur n'est valide que si la classe differential_evolution a été utilisée adéquatement.

	private:
		std::vector<double> mData;
		double mObjective;
		double mFitness;

		static double const defaultObjectiveValue;
		static double const defaultFitnessValue;
		
		friend class DifferentialEvolution;
	};

}


#endif // _DE_SOLUTION_H_
