#pragma once
#ifndef _DE_POPUPLATION_H_
#define _DE_POPUPLATION_H_


#include "Solution.h"
#include "statistics.h"


namespace de {


	class OptimizationStrategy;

    //! \brief Représente une population de l'évolution différentielle.
    //!
    //! \details Une population est un ensemble de _n_ solutions 
    //! (_n_ solutions candidates). 
    //!
    //! En fait, la classe population est une classe utilitaire encapsulant 
    //! les opérations à la gestions de _n_ solutions. Ainsi, `Population` est 
    //! le conteneur de `Solution` et donne accès à plusieurs fonctions 
    //! utilitaires.
    //!
    //! Les solutions d'une population sont manipulés différemment selon le 
    //! rôle de la population. En fait, l'implémentation courante utilise 
    //! trois populations simultanées pour les calculs internes : 
    //!  - la population courante
    //!  - les mutants
    //!  - les tests
    //!
    //! La classe population offre aussi accès aux statistiques de la 
    //! population via la classe Statistics disponible par la fonction 
    //! Population::statistics.
	class Population
	{
	public:
        Population() = default;                                     //!< Constructeur par défaut. La population est vide et aucune solution n'existe.
        Population(size_t size, SolutionDomain const & domain);     //!< Constructeur avec initialisation. Appelle la fonction population::setup.
        Population(Population const &) = default;                   //!< Constructeur de copie.
        Population(Population &&) = default;                        //!< Constructeur de déplacement.
        Population& operator=(Population const &) = default;        //!< Opérateur d'assignation de copie.
        Population& operator=(Population &&) = default;             //!< Opérateur d'assignation de déplacement.
        ~Population() = default;                                    //!< Destructeur.

		size_t size() const;                                        //!< Retourne la taille de la population (le nombre de solutions).
        Solution const & operator[](size_t pos) const;              //!< Retourne la \f$i^e\f$ solution. Aucune validation des bornes n'est réalisée. 
        Solution & operator[](size_t pos);                          //!< Retourne une référence à la \f$i^e\f$ solution. Aucune validation des bornes n'est réalisée. 
        Solution const & at(size_t pos) const;                      //!< Retourne la \f$i^e\f$ solution. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur. 
        Solution & at(size_t pos);                                  //!< Retourne une référence à la \f$i^e\f$ solution. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur. 
		Statistics const & statistics() const;                      //!< Retoure un accès aux statistiques de la population. 

		void setup(size_t size, SolutionDomain const & domain);     //!< Effectue l'initialisation de la population. Si la population possède au préalable des solutions, ils sont remplacés. La population possède _size_ solutions initialisées par _domain_. L'initialisation détermine la taille des solutions sans initialiser leurs valeurs (comme le fait la fonction Solution::setup).
		void randomize(SolutionDomain const & domain);              //!< Détermine une valeur aléatoire pour tous les solutions. 
		void clamp(SolutionDomain const & domain);                  //!< Borne la valeur de la solution dans l'intervalle défini par le domaine. 

	private:
		std::vector<Solution> mSolutions;
		Statistics mStatistics;

		void sort(OptimizationStrategy & strategy);
		void processStatistics(); // le sort doit être fait avant...

        friend class DifferentialEvolution;
		friend class MutationStrategy;
	};

}


#endif // _DE_POPUPLATION_H_
