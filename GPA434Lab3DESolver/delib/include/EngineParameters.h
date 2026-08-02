#pragma once
#ifndef _DE_ENGINE_PARAMETERS_H_
#define _DE_ENGINE_PARAMETERS_H_


#include <memory>
#include <vector>
#include "InitializationStrategy.h"
#include "MutationStrategy.h"
#include "CrossoverStrategy.h"
#include "SelectionStrategy.h"
#include "AdaptiveDomainStrategy.h"
#include "StoppingCriteriaStrategy.h"

#include "StoppingCriteriaMaxGeneration.h"


namespace de {


    //! \brief Classe déterminant les paramètres de l'algorithme de l'évolution différentielle.
    //!
    //! \details Quoique incomplète, `delib` permet une large paramétrisation des constituants de l'algorithme de l'évolution différentielle. 
    //! 
    //| EngineParameters détermine exclusivement les paramètres de l'engin de résolution DifferentialEvolution. C'est la classe ObjectiveStrategy qui spécifie le problème à résoudre.
    //!
    //! Les paramètres actuellement supportés sont : 
    //!     - la taille de la population
    //!     - le nombre maximum de génération permise
    //!     - la stratégie d'initialisation (via la classe InitializationStrategy)
    //!     - la stratégie de mutation (via la classe MutationStrategy)
    //!     - la stratégie de croisement (via la classe CrossoverStrategy)
    //!     - la stratégie de sélection (via la classe SelectionStrategy)
    //!     - la stratégie de gestion des contraintes liées au domaine (via la classe AdaptiveDomainStrategy)
    //!     - les critères d'arrêt (via la class StoppingCriteriaStrategy)
    //!
    //! DifferentialEvolution utilise tous ces paramêtres pour contrôler le déroulement de l'évolution. 
    //! 
    //! Le tableau suivant présente un résumé de ces paramètres
    //!     | Paramètre                     | Description                                                       | Valeur par défaut         | Commentaires  |
    //!     | :---------------------------: | :---------------------------------------------------------------- | :-----------------------: | :-----------  |
    //!     | Taille de la population       | Nombre de solutions candidates.                                   | 25                        | La taille de la population est limitée par les constantes minimum_population_size (5) et maximum_population_size (1000). |
    //!     | Nombre de génération maximum  | Le nombre d'itération maximum autorisé l'arrêt de l'évolution.    | 150                       | Le nombre maximum de génération est limitée par les constantes minimum_generation_count (10) et maximum_generation_count (100000). |
    //!     | Stratégie de mutation         | Algorithme utilisé pour l'étape de mutation.                      | MutationRand1             | ... |
    //!     | Facteur de mutation 'f'       | Le facteur de mutation 'f' [0, 2].                                | 1                         | ... |
    //!     | Stratégie de croisement       | Algorithme utilisé pour l'étape de croisement.                    | CrossoverBinomial         | ... |
    //!     | Taux de croisement 'R'        | Le taux de croisement 'R' [0, 1].                                 | 0.5                       | ... |
    //!     | Stratégie de sélection        | Algorithme utilisé pour l'étape de sélection.                     | SelectionBestFitness      | ... |
    //!     | Critères d'arrêt              | Algorithmes utilisés pour évaluer si l'algorithme termine les évolutions. | aucun supplémentaire \n voir détail plus bas | ... |
    //!  
    //! On remarque que plusieurs critères d'arrêt peuvent être utilisés simultanément. Ainsi, il est possible de préciser plusieurs conditions où l'algorithme termine l'évolution. Il existe cependant un critère d'arrêt implicite à l'algorithme et c'est le nombre de génération maximum. Formellement, le nombre de génération maximum est un critère d'arrêt et est géré comme tel par l'algorithme. Toutefois, il est obligatoire de définir sa valeur et il est impossible de retirer ce critère. Il est donc possible de n'avoir aucun autre critère d'arrêt supplémentaire et c'est l'implémentation par défaut.
    //! 
	class EngineParameters
	{
	public:
		EngineParameters();                                                 //!< Constructeur par défaut. Tous les paramètres sont à leur valeur par défaut.
        EngineParameters(EngineParameters const & other);                   //!< Constructeur de copie interdit.
        EngineParameters(EngineParameters && other);                        //!< Constructeur de déplacement.
        EngineParameters& operator=(EngineParameters const & lhs);          //!< Opérateur d'assignation de copie interdit.
        EngineParameters& operator=(EngineParameters && lhs);               //!< Opérateur d'assignation de déplacement.
        ~EngineParameters() = default;                                      //!< Destructeur.

		static size_t minimumPopulationSize();                              //!< Retourne la taille de population minimum permise.
		static size_t maximumPopulationSize();                              //!< Retourne la taille de population maximum permise.
		static size_t defaultPopulationSize();                              //!< Retourne la taille de population par défaut.
        static size_t minimumGenerationCount();                             //!< Retourne le nombre de génération minimum permis.
        static size_t maximumGenerationCount();                             //!< Retourne le nombre de génération maximum permis.
        static size_t defaultGenerationCount();                             //!< Retourne le nombre de génération par défaut.

		size_t populationSize() const;                                      //!< Retourne la taille de la population définie.
		size_t maximumGeneration() const;                                   //!< Retourne le nombre de génération maximum défini.
		size_t stoppingCriteriaSize() const;                                //!< Retourne le nombre de critère d'arrêt effectif. Cet actuateur exclue du compte le critère d'arrêt lié au nombre de générations maximum. Il retourne ceux qui ont été ajouté.

        InitializationStrategy* initializationStrategy() const;             //!< Accesseur retournant la stratégie d'initialisation. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.
        MutationStrategy* mutationStrategy() const;                         //!< Accesseur retournant la stratégie de mutation. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.
        CrossoverStrategy* crossoverStrategy() const;                       //!< Accesseur retournant la stratégie de croisement. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.
        SelectionStrategy* selectionStrategy() const;                       //!< Accesseur retournant la stratégie de sélection. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.
        AdaptiveDomainStrategy* adaptiveDomainStrategy() const;             //!< Accesseur retournant la stratégie de gestion des contraintes liées au domaine. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.
        std::vector<StoppingCriteriaStrategy*> stoppingCriteriaStrategy() const; //!< Accesseur retournant les critères d'arrêt. *Attention, retourne une copie (un clone) de l'objet source. Celui appelant cette fonction devient responsable de l'allocation de mémoire réalisée et doit libérer adéquatement cette dernière.

		void setPopulationSize(size_t size);                                //!< Mutateur permettant de définir la taille de la population. Si la taille indiquée est à l'extérieur des valeurs minimum et maximum permises, la valeur est mise à la limite la plus près.
		void setMaxGeneration(size_t count);                                //!< Mutateur permettant de définir le nombre de génération maximum. Si la taille indiquée est à l'extérieur des valeurs minimum et maximum permises, la valeur est mise à la limite la plus près.

		void setInitializationStrategy(InitializationStrategy * strategy);  //!< Mutateur définissant la stratégie d'initialisation. L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.
		void setMutationStrategy(MutationStrategy * strategy);              //!< Mutateur définissant la stratégie de mutation. L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.
		void setCrossoverStrategy(CrossoverStrategy * strategy);            //!< Mutateur définissant la stratégie de croisement. L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.
		void setSelectionStrategy(SelectionStrategy * strategy);            //!< Mutateur définissant la stratégie de sélection.  L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.
        void setAdaptiveDomainStrategy(AdaptiveDomainStrategy* strategy);   //!< Mutateur définissant la stratégie de gestion des contraintes liées au domaine.  L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.

        double crossoverRate() const;                                       //!< Accesseur retournant le taux de croisement 'R'. Retourne -1.0 si la stratégie est non définie.
        double mutationFactor() const;                                      //!< Accesseur retournant le facteur de mutation 'f'. Retourne -1.0 si la stratégie est non définie.
        void setCrossoverRate(double rate);                                 //!< Mutateur définissant le taux de croisement 'R'. La valeur est bornée entre 0 et 1. Ne fait rien si la stratégie est non défnie.
        void setMutationFactor(double factor);                              //!< Mutateur définissant le facteur de mutation 'f'. La valeur est bornée entre 0 et 2. Ne fait rien si la stratégie est non défnie.

		bool addStoppingCriteriaStrategy(StoppingCriteriaStrategy * strategy);  //!< Fonction utilitaire permettant d'ajouter un critère d'arrêt. L'objet passé en paramètre doit être alloué dynamiquement et un transfert de propriété est donne à cette classe. Ainsi, le propriétaire de cet objet devient la classe engine_parameter et il est déconseillé d'y accéder sans passer par celle-ci.
		void clearStoppingCriteraStrategy();                                //!< Vide tous les critères d'arrêts. À la fin de cette fonction, il n'existe que le critère d'arrêt déterminer par le nombre de génération maximum.

		bool isReady() const;                                               //!< Retourne vrai si tous les paramètres sont définis conformément à l'usage de differential_evolution.
		void reset();                                                       //!< Remet en place tous les paramètres par défaut.

		bool isStoppingCriteriaMet(DifferentialEvolution const & de) const; //!< Détermine si tous les critères d'arrêt sont satisfaits (incluant le critère d'arrêt lié au nombre de génération maximum). 
	
        void swap(EngineParameters & parameters);                           //!< Échange les paramètres avec ceux de l'objet passé en paramètre.
        void copyFrom(EngineParameters const & other);                      //!< Copie les paramètres de l'objet passé en paramètre.
        void copyTo(EngineParameters & other) const;                        //!< Copie les paramètres dans l'objet passé en paramètre.

	private:
		size_t mPopulationSize;
		std::unique_ptr<InitializationStrategy>  mInitializationStrategy;
		std::unique_ptr<MutationStrategy>  mMutationStrategy;
		std::unique_ptr<CrossoverStrategy> mCrossoverStrategy;
		std::unique_ptr<SelectionStrategy> mSelectionStrategy;
		std::unique_ptr<AdaptiveDomainStrategy> mAdaptiveDomainStrategy;
		std::vector<std::unique_ptr<StoppingCriteriaStrategy>> mStoppingCriteriaStrategies;
		StoppingCriteriaMaxGeneration mStoppingCriteriaMaxGeneration;

		static const size_t mMinimumPopulationSize;
		static const size_t mMaximumPopulationSize;
		static const size_t mDefaultPopulationSize;
		static const size_t mMinimumGenerationCount;
		static const size_t mMaximumGenerationCount;
		static const size_t mDefaultGenerationCount;
		
        friend class DifferentialEvolution;
	};

}

#endif // _DE_ENGINE_PARAMETERS_H_
