#pragma once
#ifndef _DE_PEAK_FUNCTION_SOLUTION_H_
#define _DE_PEAK_FUNCTION_SOLUTION_H_


#include "SolutionStrategy.h"


namespace de {

	//! \brief Classe représentant une stratégie de solution pour la fonction 
	//! 'peak' de Matlab.
	//!
	//! \details Cette classe hérite de `SolutionStrategy` et représente une 
	//! stratégie spécifique pour la résolution de la fameuse fonction 'peak' 
	//! de Matlab.
	//! 
	//! 
	//! 
	//! \class PeakFunctionSolution
	//!
	//! \brief Classe représentant une stratégie de solution pour identifier les 
	//! extrémums de la célèbre fonction 'peak' de Matlab.
	//!
	//! \details Cette classe hérite de `SolutionStrategy` et est conçue spécifiquement pour
	//! résoudre la fonction 'peak' de Matlab. Elle représente une stratégie de solution
	//! adaptée pour explorer et identifier les points optimaux (minimum, maximum ou les deux) de cette fonction.
	//! 
	//! La classe sert de base à trois autres classes spécialisées dans la recherche des valeurs minimales,
	//! maximales, et des extrema de la fonction 'peak'.
	class PeakFunctionSolution : public SolutionStrategy
	{
	public:
		//! 
		PeakFunctionSolution(size_t number_of_points = 1);							//!< Constructeur par défaut. number_of_points est limité dans l'intervalle [1, 6]
		PeakFunctionSolution(PeakFunctionSolution const&) = default;				//!< Constructeur de copie.
		PeakFunctionSolution(PeakFunctionSolution&&) = default;						//!< Constructeur de déplacement.
		PeakFunctionSolution& operator=(PeakFunctionSolution const&) = default;		//!< Opérateur d'assignation de copie.
		PeakFunctionSolution& operator=(PeakFunctionSolution&&) = default;			//!< Opérateur d'assignation de déplacement.
		~PeakFunctionSolution() override = default;									//!< Destructeur.
		//! 
		//! \brief Retourne une représentation textuelle de la solution.
		//! \param solution La solution à représenter.
		//! \returns Une chaîne de caractères représentant la solution.
		std::string toString(de::Solution const& solution) const override;


		EngineParameters engineParameters() const override;                            //!< Retourne les paramètres du moteur adaptés à cette problématique.

		//! 
		//! \brief Calcule la valeur de la fonction 'peak' de Matlab.
		//! \param x La coordonnée x de la solution.
		//! \param y La coordonnée y de la solution.
		//! \returns La valeur de la fonction 'peak' aux coordonnées (x, y).
		static double peak(double x, double y);

	protected:
		static const size_t sPrecision;												//!< La précision souhaitée pour les calculs.
		static const std::string sTitle;											//!< Le titre utilisé pour la représentation textuelle.
	};


} // namespace de

#endif // _DE_PEAK_FUNCTION_SOLUTION_H_