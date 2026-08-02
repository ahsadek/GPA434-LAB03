#pragma once
#ifndef _DE_STOPPING_CRITERIA_STRATEGY_H_
#define _DE_STOPPING_CRITERIA_STRATEGY_H_


#include <string>
#include "Strategy.h"


namespace de {


	class DifferentialEvolution;


    //! \brief Classe de base pour les stratégies de critère d'arrêt.
    //!
    //! \details Cette classe fournit une interface pour les différentes stratégies de critère d'arrêt utilisées dans l'algorithme d'évolution différentielle.
    class StoppingCriteriaStrategy : public Strategy
    {
    public:
        StoppingCriteriaStrategy(std::string const& name, std::string const& summary, std::string const& description);//!< Constructeur .
        StoppingCriteriaStrategy(StoppingCriteriaStrategy const&) = default;            //!< Constructeur de copie.
        StoppingCriteriaStrategy(StoppingCriteriaStrategy&&) = default;                 //!< Constructeur de déplacement.
        StoppingCriteriaStrategy& operator=(StoppingCriteriaStrategy const&) = default; //!< Opérateur d'assignation de copie.
        StoppingCriteriaStrategy& operator=(StoppingCriteriaStrategy&&) = default;      //!< Opérateur d'assignation de déplacement.
        ~StoppingCriteriaStrategy() override = default;                                 //!< Destructeur.

        virtual bool isStopping(DifferentialEvolution const& de) const = 0;             //!< Détermine si le critère d'arrêt est atteint.
    };


}



#endif // _DE_STOPPING_CRITERIA_STRATEGY_H_
