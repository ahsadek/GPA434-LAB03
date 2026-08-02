#pragma once
#include "QDESolutionPanel.h"
#include <SolutionStrategy.h>

// Le problème de la boîte ouverte.
// 
// Vous avez une surface rectangulaire d'une largeur et d'une hauteur déterminée (width x height).
//
//    +--------------------------------------+     -+
//    |                                      |      |
//    |                                      |      |
//    |                                      |      |
//    |                                      |      |
//    |                                      |      \_ height
//    |                                      |      /
//    |                                      |      |
//    |                                      |      |
//    |                                      |      |
//    |                                      |      |
//    +--------------------------------------+     -+
//
//    +------------------v-------------------+
//                       |
//                     width
// 
// On vous demande de couper les 4 coins selon un carré de taille : x
//
//    +-------+----------------------+-------+     -+
//    |       |                      |       |      |
//    |       |                      |       |      >- x
//    |       |                      |       |      |
//    +-------+                      +-------+     -+
//    |                                      |
//    |                                      |
//    +-------+                      +-------+     -+
//    |       |                      |       |      |
//    |       |                      |       |      >- x
//    |       |                      |       |      |
//    +-------+----------------------+-------+     -+
//
//    +---v---+                      +---v---+ 
//        |							     |
//        x							     x
//
// Pour que finalement, après avoir plié les 4 panneaux, vous otenez la boîte ouverte ayant le plus grand volume possible.
//       
//                                       ________ 
//                       ________--------       |-_  
//       ________--------                       |  -_
//      |-_                                     |    -_
//      |  -_                                   |________
//      |    -_                  ________--------       |
//      |      - ________--------						|
//      |       |                                       |
//      -_      |                                       |
//        -_    |                               ________|
//          -_  |                ________--------
//            -_|________--------
//
//

class QImageViewer;
class QScrollBar;
class QHBoxLayout;
class QPainter;



//! \brief Panneau représentant spécifiquement le problème de la boîte ouverte.
class QDEOpenBoxPanel : public QDESolutionPanel
{
	Q_OBJECT

public:
	// Constructors, destructor and assignment operators
	QDEOpenBoxPanel(QWidget * parent = nullptr);
	QDEOpenBoxPanel(QDEOpenBoxPanel const &) = default;
	QDEOpenBoxPanel(QDEOpenBoxPanel &&) = default;
	QDEOpenBoxPanel& operator=(QDEOpenBoxPanel const &) = default;
	QDEOpenBoxPanel& operator=(QDEOpenBoxPanel &&) = default;
	~QDEOpenBoxPanel() override = default;

	// Box dimensions getter
	double boxWidth() const;
	double boxHeight() const;
	
	// QDESolutionPanel interface returning the description of the problem
	de::SolutionStrategy* buildSolution() const override;

public slots:
	// QDESolutionPanel interface updating the visualization of the problem
	void updateVisualization(QDEAdapter const & de) override;

private:
	QImageViewer* mVisualizationLabel;
	QScrollBar * mWidthScrollBar;
	QScrollBar * mHeightScrollBar;
	QHBoxLayout * buildScrollBarLayout(QScrollBar * & sb);
	void drawBox(QPainter & painter, QPointF const & boxCenterPos, double boxSize, double cutSize);

	class OpenBoxStrategy;

	static const QString sDescription;
};




//! \brief Classe représentant une stratégie de solution pour la 
//! résolution du problème de la boîte ouverte.
class QDEOpenBoxPanel::OpenBoxStrategy : public de::SolutionStrategy
{
public:
	OpenBoxStrategy(double width = 1.0, double height = 1.0);
	OpenBoxStrategy(OpenBoxStrategy const &) = default;
	OpenBoxStrategy(OpenBoxStrategy &&) = default;
	OpenBoxStrategy& operator=(OpenBoxStrategy const &) = default;
	OpenBoxStrategy& operator=(OpenBoxStrategy &&) = default;
	~OpenBoxStrategy() override = default;

	std::string toString(de::Solution const & ag) const override;

	DEFINE_OVERRIDE_CLONE_METHOD(OpenBoxStrategy)	     //!< Macro définissant automatiquement la substitution de la méthode de clonage.

protected:
	double process(de::Solution const & ag) override;

private:
	double mWidth;
	double mHeight;
};

