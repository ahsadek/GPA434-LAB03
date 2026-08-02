#pragma once


#include <QWidget>
#include <SolutionStrategy.h>
#include "QDEAdapter.h"


//! 
//! \class QDESolutionPanel
//! 
//! \brief Classe abstraite servant de définition commune aux panneaux 
//! représentant un problème spécifique.
//! 
//! Cette classe est un `QWidget`, hérite de `QWidget`, et fournit des 
//! méthodes abstraites (virtuelles pures) pour la gestion des solutions.
//! 
//! La classe est conçue pour être héritée par d'autres classes qui 
//! implémentent des stratégies spécifiques pour résoudre des problèmes. 
//! Cette classe offre principalement l'opportunité de :
//! - créer une solution spécifique
//! - d'informer l'engin d'évolution différentielle lorsque la 
//!   paramétrisation de la solution change
//! - visualiser la simulation pendant l'évolution
//! 
//! Lorsqu'on désire mettre dans l'application un panneau de résolution 
//! d'un problème, les étapes suivantes sont à considérer :
//! - d'abord, la nouvelle classe doit hériter de celle-ci
//! - ensuite, étant un _widget_, cette classe doit assembler tous les 
//!   _widgets_ nécessaires à :
//!		- la configuration du problème avant l'évolution
//!		- la visualisation de la solution ou des solutions pendant l'évolution
//! - substituer (_override_) la méthode `buildSolution()` pour instancier le problème à résoudre
//! - substituer (_override_) la méthode `updateVisualization()` pour mettre à jour la visualisation
//! - s'assurer que le signal `parameterChanged()` est émis lorsque les paramètres changent
//! - finalement, ajouter ce panneau dans l'instance de QDESolutionTabPanel
class QDESolutionPanel : public QWidget
{
	Q_OBJECT

public:
	QDESolutionPanel(QWidget* parent = nullptr);					//!< Constructeur par défaut, prend optionnel un widget parent.
	~QDESolutionPanel() override = default;							//!< Destructeur (virtuel) par défaut.

	QDESolutionPanel(QDESolutionPanel const&) = delete;				//!< Constructeur de copie par défaut.
	QDESolutionPanel(QDESolutionPanel&&) = delete;					//!< Constructeur de déplacement par défaut.
	QDESolutionPanel& operator=(QDESolutionPanel const&) = delete;	//!< Opérateur d'affectation par copie par défaut.
	QDESolutionPanel& operator=(QDESolutionPanel&&) = delete;		//!< Opérateur d'affectation par déplacement par défaut.


	//! \brief Construit une solution.
	//! 
	//! \details Cette méthode est appelée par l'application au moment opportun 
	//! pour créer la solution à résoudre. Notamment, lorsqu'il y a un 
	//! changement d'onglet dans l'application.
	//! 
	//! Il est important de retourner une solution valide allouée dynamiquement. 
	//! Le moteur d'évolution différentielle prend possession de cette 
	//! allocation.
	//! 
	//! Cette méthode est abstraite (virtuel pure).
	virtual de::SolutionStrategy* buildSolution() const = 0;

signals:
	//! \brief Signal émis lorsque les paramètres de la solution changent.
	//!
	//! \details Ce signal n'est jamais émis par la classe de base. Il est 
	//! attendu que les classes dérivées émettent ce signal lorsque les 
	//! paramètres de la solution changent. C'est la responsabilité des 
	//! classes dérivées d'émettre le signal à chaque opportunité où la 
	//! configuration du problème change.
	//! 
	//! \code
	//! // Exemples d'émission du signal
	//! 
	//! // Émission explicite
	//!	emit parameterChanged();
	//! 
	//! // Il est possible d'émettre un signal en réponse à un autre signal
	//! // Pour cet exemple :
	//! // - QMySolutionPanel est une classe dérivée de QDESolutionPanel
	//! // - myScrollBar est un QScrollBar
	//! connect(myScrollBar, &QScrollBar::valueChanged, this, &QMySolutionPanel::parameterChanged);
	//! \endcode
	void parameterChanged();

public slots:
	//! \brief Met à jour la visualisation.
	//! 
	//! \details Cette méthode est appelée par l'application au moment 
	//! opportun afin d'offrir l'opportunité de mettre à jour interactivement 
	//! des informations pendant l'évolution du problème.
	//! 
	//! Prendre note que cette méthode est aussi appelée avant l'évolution et 
	//! qu'une représentation du problème est possible pendant sa paramétrisation.
	//! 
	//! Cette méthode est abstraite (virtuelle pure). La substitution (_override_) 
	//! de cette méthode implique une analyse de la solution et de la population 
	//! par l'objet deAdapter passé en argument.
	//! 
	//! \params deAdapter L'adaptateur d'évolution différentielle.
	virtual void updateVisualization(QDEAdapter const& deAdapter);
};

