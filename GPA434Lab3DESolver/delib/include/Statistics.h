#pragma once
#ifndef _DE_STATISTICS_H_
#define _DE_STATISTICS_H_


#include "Solution.h"


namespace de {


    //! \brief Représente des données statistiques simples.
    //!
    //! \details Cette classe permet de construire et de maintenir des 
	//! statistiques de base sur une population ou sur l'évolution. 
    //!
    //! On retrouve d'abord ces données représentant une synthèse des 
	//! résultats observés par la fonction de fitness :
    //!     - le nombre de valeurs observées    
    //!     - la valeur minimum observée        
    //!     - la valeur maximum observée        
    //!     - la somme des valeurs observées    
    //!     - la moyenne des valeurs observées  
    //!     - l'écart type des valeurs observées
    //! 
    //! Ensuite, on retroue une copie des trois solutions suivantes :
    //!     - la meilleure solution
    //!     - la solution médiane
    //!     - la pire solution
	class Statistics
	{
	public:
		Statistics() = default;                                 //!< Constructeur par défaut. Les statistiques sont initialisées comme le fait la fonction reset.
		Statistics(Statistics const &) = default;               //!< Constructeur de copie.
        Statistics(Statistics &&) = default;                    //!< Constructeur de déplacement.
        Statistics& operator=(Statistics const &) = default;    //!< Opérateur d'assignation de copie.
        Statistics& operator=(Statistics &&) = default;         //!< Opérateur d'assignation de déplacement.
        ~Statistics() = default;                                //!< Destructeur.

		size_t count() const;                                   //!< Retourne le nombre de données utilisées pour construire les statistiques disponibles.
		double minimum() const;                                 //!< Retourne la valeur de fitnesse la plus basse.
		double maximum() const;                                 //!< Retourne la valeur de fitnesse la plus élevée.
		double sum() const;                                     //!< Retourne la somme des fitness.
		double average() const;                                 //!< Retourne la moyenne des fitness.
		double stdev() const;                                   //!< Retourne l'écart type des fitness.

		Solution const & bestSolution() const;                  //!< Retourne une copie de la meilleure solution.
		Solution const & medianSolution() const;                //!< Retourne une copie de la solution médiane.
		Solution const & worstSolution() const;                 //!< Retourne une copie de la solution la moins performante.
                                                                 
		void reset();                                           //!< Réinitialise les statistiques. 

	private:
		// approche naïve (peu stable numériquement)... à améliorer.
		size_t mCount;				
		double mMinimum{};
		double mMaximum{};
		double mSum{};
		double mSum2{};
		double mAverage{};
		double mVariance{};
		double mStdDev{};

		Solution mBestSolution;
		Solution mMedianSolution;
		Solution mWorstSolution;

		void build(double value);	// ajoute une valeur sans faire les calculs de moyenne et d'écart type.
		void add(double value);		// ajoute une valeur et réalise les calculs de moyenne et d'écart type.
		void process();				// réalise les calculs de moyenne et d'écart type.

		friend class Population;
		friend class History;
	};

}

#endif // _DE_STATISTICS_H_
