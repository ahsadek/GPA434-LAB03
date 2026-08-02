#pragma once
#ifndef _DE_HISTORY_H_
#define _DE_HISTORY_H_


#include <vector>
#include "Statistics.h"


namespace de {

    //! \brief Représente l'historique des statistiques tout au long de 
	//! l'évolution.
    //!
    //! \details Cette classe permet de maintenir un résumé des données 
	//! obtenue lors de l'évolution. En fait, une copie des statistiques de la 
	//! population est ajoutée dans l'historique. Ainsi, il est possible 
	//! d'avoir une vue d'ensemble du comportement de l'algorithme. 
	class History
	{

	public:
		History() = default;                                //!< Constructeur par défaut. L'historique est vide.
        History(History const &) = default;                 //!< Constructeur de copie.
        History(History &&) = default;                      //!< Constructeur de déplacement.
        History& operator=(History const &) = default;      //!< Opérateur d'assignation de copie.
        History& operator=(History &&) = default;           //!< Opérateur d'assignation de déplacement.
        ~History() = default;                               //!< Destructeur.

		size_t size() const;                                //!< Retourne la taille de l'historique.
        Statistics const & operator[](size_t pos) const;    //!< Retourne l'historique à la position indiquée. Aucune validation des bornes n'est réalisée. 
		Statistics const & last() const;                    //!< Fonction utilitaire retournant le dernier historique.

		void getRange(double & xMin, double & xMax, double & yMin, double & yMax) const; //!< Fonction permettant de retournée les limites des données incluses dans l'historique. \f$x\f$ représentant le temps alors que \f$y\f$ les valeurs de fitness observées. Cette fonction peut être pratique lors de la peprésentation des limites de l'historique pour un affichage graphique par exemple.

	private:
		std::vector<Statistics> mStatistics;
		Statistics mStatOnMinimum;
		Statistics mStatOnMaximum;

		void clear();
		void add(Statistics const & stat);

		friend class DifferentialEvolution;
	};

}

#endif // _DE_HISTORY_H_
