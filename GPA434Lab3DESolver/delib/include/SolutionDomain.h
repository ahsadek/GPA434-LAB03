#pragma once
#ifndef _DE_SOLUTION_DOMAIN_H_
#define _DE_SOLUTION_DOMAIN_H_


#include <vector>
#include "Interval.h"


namespace de {

	//! \brief Représente les limites du problème.
	//!
	//! \details SolutionDomain correspond à l'ensemble des intervals définis pour chacune des dimensions du problème.
    //!
    //! L'évolution différentielle définie deux vecteurs \f$l\f$ et \f$u\f$ représentant le domaine de validité de chacune des dimensions du problème. La classe SolutionDomain représente ces informations via un vecteur d'interval. 
	//! Le vecteur d'interval est de la même dimension que le problème à résoudre. Les valeurs \f$l_i\f$ et \f$u_i\f$ sont stockées au \f$i^e\f$ interval du vecteur.
	//!
	//! Il est important de noter que cette implémentation de la librairie utilise les vecteur \f$l\f$ et \f$u\f$ seulement lors de la définition du problème et à l'initialisation de la simulation. La validation des intervals n'est pas faite lors de l'évolution elle-même. Par conséquent, il est possible que la simulation donne des résultats à l'extérieure de ces intervals. 
	class SolutionDomain
	{
	public:
		SolutionDomain() = default;										//!< Constructeur par défaut.
		SolutionDomain(size_t size);									//!< Constructeur avec taille d'initialisation.
		SolutionDomain(size_t size, double lower, double upper);		//!< Constructeur avec taille et bornes d'initialisation.
		SolutionDomain(SolutionDomain const &) = default;				//!< Constructeur de copie.
		SolutionDomain(SolutionDomain &&) = default;					//!< Constructeur de déplacement.
		SolutionDomain& operator=(SolutionDomain const &) = default;	//!< Opérateur d'assignation de copie.
		SolutionDomain& operator=(SolutionDomain &&) = default;			//!< Opérateur d'assignation de déplacement.
		~SolutionDomain() = default;									//!< Destructeur.

		size_t size() const;											//!< Retourne la taille du vecteur d'interval (la taille du problème à résoudre).
		Interval const & operator[](size_t pos) const;					//!< Retourne le ie interval. Aucune validation des bornes n'est réalisée.
		Interval & operator[](size_t pos);								//!< Retourne une référence au ie interval. Aucune validation des bornes n'est réalisée.
		Interval at(size_t pos) const;									//!< Retourne le ie interval. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur.
		Interval & at(size_t pos);										//!< Retourne une référence au ie interval. La validation des bornes est réalisée. L'exception std::out_of_range est lancée si la position est à l'extérieur des bornes du vecteur.

		void resize(size_t size);										//!< Redimensionne la taille du problème. Chacune des bornes étant réinitialisées selon la classe interval. 
		void resize(size_t size, double lower, double upper);			//!< Redimensionne la taille du problème. Chacune des bornes est fixées aux même valeurs déterminées par lower et higher.

		void set(double lower, double upper);							//!< Assigne, pour chacun des intervals, les mêmes valeurs lower et higher.
		void reset();													//!< Assigne, pour chacun des intervals, les valeurs par défaut telles que définies par la classe interval.

	private:
		std::vector<Interval> mDomain;
	};

}


#endif // _DE_SOLUTION_DOMAIN_H_
