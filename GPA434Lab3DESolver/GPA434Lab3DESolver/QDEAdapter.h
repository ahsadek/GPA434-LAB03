#pragma once


#include <QObject>
#include <DifferentialEvolution.h>
#include <EngineParameters.h>


//! 
//! \class QDEAdapter
//! 
//! \brief Classe servant d'interface entre l'algorithme d'évolution 
//! différentielle et le reste de l'application.
//! 
//! Il est intéressant d'observer que la bibliothèque `delib` est entièrement 
//! indépendante de `Qt`. Ceci a un impact important sur la conception 
//! générale de l'application. L'algorithme ne permet pas d'interagir 
//! _naturellement_ avec `Qt`, ses signaux et ses connecteurs (_slots_).  
//! 
//! Ainsi, le rôle de cette classe est d'offrir une interface _naturelle_ 
//! pour travailler avec `Qt`.
//! 
//! QDEAdapter hérite de QObject et fournit un ensemble de méthodes, de 
//! signaux et de connecteurs pour manipuler et surveiller une instance 
//! de l'algorithme d'évolution différentielle. 
//! 
//! Elle offre des fonctionnalités pour configurer l'algorithme, réinitialiser 
//! et faire avancer l'évolution, obtenir des informations sur la solution 
//! actuelle et la population, ainsi que la vérification de l'état de 
//! l'évolution.
//! 
//! Cette classe, permet ainsi l'utilisation simple de `Qt` avec `delib`. 
//! La bibliothèque `delib` est volontairement conçue pour ne pas être 
//! dépendante et contrainte par les particularités de `Qt`. Ainsi, 
//! `QDEAdapter` permet le meilleur des deux mondes en acceptant le compromis 
//! d'un faible coût de performance.
//! 
class QDEAdapter : public QObject
{
	Q_OBJECT

public:
	// explicit is added to prevent constructing a QDEAdapter from indirect QObject while QDEAdapter is required as argument into a function.
	//  - see QDEController constructor first argument for an example 
	//  - some students constructed the QDEController with the first argument as 'this' 
	//    in the DEApplication self constructor -> difficult to debug by the students 
	explicit QDEAdapter(QObject* parent = nullptr);		//!< Constructeur par défaut, prend un QObject parent en option.
	QDEAdapter(QDEAdapter const&) = default;			//!< Constructeur de copie par défaut.
	QDEAdapter(QDEAdapter&&) = default;					//!< Constructeur de déplacement par défaut.
	QDEAdapter& operator=(QDEAdapter const&) = default;	//!< Opérateur d'affectation par copie par défaut.
	QDEAdapter& operator=(QDEAdapter&&) = default;		//!< Opérateur d'affectation par déplacement par défaut.
	~QDEAdapter() override = default;					//!< Destructeur par défaut.

	bool isReady();										//!< Vérifie si l'adaptateur est prêt, c'est-à-dire, si le moteur d'évolution différentielle est prêt.
	size_t currentGeneration() const;					//!< Renvoie le numéro de la génération actuelle.
	bool isStoppingCriteriaReached() const;				//!< Vérifie si le critère d'arrêt a été atteint.

	de::SolutionStrategy const& solution();				//!< Renvoie la solution actuelle. Cette fonction lancera une exception si aucune solution n'est définie.

	QString bestSolutionInfo() const;					//!< Renvoie une représentation textuelle de la meilleure solution obtenue.
	de::History const& statisticsHistory() const;		//!< Renvoie l'historique des statistiques en lecture seule.

	de::Population actualPopulation() const;			//!< Renvoie une copie de la population actuelle.

public slots:
	de::DifferentialEvolution::SetupState setup(de::SolutionStrategy* solution); //!< Configure l'adaptateur avec des paramètres de moteur et une stratégie de solution.
	void setEngineParameters(de::EngineParameters const& parameters); //!< Définit les paramètres du moteur d'évolution différentielle.
	void stepEvolution();								//!< Effectue une étape de l'évolution.
	void reset();										//!< Réinitialise la simulation à son état initial (tel que défini par EngineParameters).

signals:
	void oneEvolutionStepped();							//!< Signal émis après une étape de l'évolution.
	void wasReset();									//!< Signal émis après la réinitialisation de l'adaptateur.
	void stoppingCriteriaReached();						//!< Signal émis lorsque le critère d'arrêt est atteint.

private:
	de::DifferentialEvolution mDE;						//!< Instance de l'algorithme d'évolution différentielle.

};

