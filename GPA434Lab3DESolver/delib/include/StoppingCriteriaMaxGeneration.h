#pragma once
#ifndef _DE_STOPPING_CRITERIA_GENERATION_H_
#define _DE_STOPPING_CRITERIA_GENERATION_H_


#include "StoppingCriteriaStrategy.h"


namespace de {

    //! \brief Stratégie de critère d'arrêt basée sur le nombre maximal de générations.
    //!
    //! \details Cette classe implémente une stratégie d'arrêt qui se déclenche lorsque le nombre de générations dépasse une valeur maximale spécifiée.
    class StoppingCriteriaMaxGeneration : public StoppingCriteriaStrategy
    {
    public:
        StoppingCriteriaMaxGeneration(size_t maxGeneration = 250);                                  //!< Constructeur avec le nombre maximal de générations.
        StoppingCriteriaMaxGeneration(StoppingCriteriaMaxGeneration const&) = default;              //!< Constructeur de copie.
        StoppingCriteriaMaxGeneration(StoppingCriteriaMaxGeneration&&) = default;                   //!< Constructeur de déplacement.
        StoppingCriteriaMaxGeneration& operator=(StoppingCriteriaMaxGeneration const&) = default;   //!< Opérateur d'assignation de copie.
        StoppingCriteriaMaxGeneration& operator=(StoppingCriteriaMaxGeneration&&) = default;        //!< Opérateur d'assignation de déplacement.
        ~StoppingCriteriaMaxGeneration() override = default;                                        //!< Destructeur.

        size_t maxGeneration() const;                                                               //!< Retourne le nombre maximal de générations.
        void setMaxGeneration(size_t maxGeneration);                                                //!< Définit le nombre maximal de générations.

        bool isStopping(DifferentialEvolution const& de) const override;                            //!< Détermine si le critère d'arrêt est atteint.

        DEFINE_OVERRIDE_CLONE_METHOD(StoppingCriteriaMaxGeneration)                                 //!< Macro définissant automatiquement la substitution de la méthode de clonage.		

	private:
		size_t mMaxGeneration{ 250 };
	};

}


#endif // _DE_STOPPING_CRITERIA_GENERATION_H_
