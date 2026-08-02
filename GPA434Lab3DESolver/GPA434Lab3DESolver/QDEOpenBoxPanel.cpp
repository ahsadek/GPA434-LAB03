#include "QDEOpenBoxPanel.h"


#include <QFrame>
#include <QGroupBox>
#include <QLabel>
#include <QScrollBar>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPainter>

#include "QImageViewer.h"


QDEOpenBoxPanel::QDEOpenBoxPanel(QWidget * parent)
	:	QDESolutionPanel(parent),
		mVisualizationLabel{ new QImageViewer },
		mWidthScrollBar{ nullptr },
		mHeightScrollBar{ nullptr }
{
	// create the 'input parameters' group box and its contents
	QGroupBox * parameterGroupBox{ new QGroupBox("Paramètres") };
	QFormLayout * parameterLayout{ new QFormLayout };
	parameterLayout->addRow("Largeur", buildScrollBarLayout(mWidthScrollBar));
	parameterLayout->addRow("Hauteur", buildScrollBarLayout(mHeightScrollBar));
	parameterGroupBox->setLayout(parameterLayout);

	// create the 'visualization' group box and its contents
	QGroupBox * visualizationGroupBox{ new QGroupBox("Visualisation") };
	QVBoxLayout * visualizationLayout{ new QVBoxLayout };
	QLabel* visualizationTitle{ new QLabel("Représentation de chaque solution") };
	QLabel* visualizationNote{ new QLabel("<span style=\"font-style: italic;\">Triès du haut vers le bas et de gauche à droite</span>") };
	visualizationNote->setAlignment(Qt::AlignRight);
	visualizationLayout->addWidget(visualizationTitle);
	visualizationLayout->addWidget(mVisualizationLabel);
	visualizationLayout->addWidget(visualizationNote);
	visualizationGroupBox->setLayout(visualizationLayout);

	// create the main layout
	QVBoxLayout * layout{ new QVBoxLayout(this) };
	layout->addWidget(parameterGroupBox);
	layout->addWidget(visualizationGroupBox);
}

double QDEOpenBoxPanel::boxWidth() const
{
	return static_cast<double>(mWidthScrollBar->value());
}

double QDEOpenBoxPanel::boxHeight() const
{
	return static_cast<double>(mHeightScrollBar->value());
}

de::SolutionStrategy* QDEOpenBoxPanel::buildSolution() const
{
	return new OpenBoxStrategy(mWidthScrollBar->value(), mHeightScrollBar->value());
}

QHBoxLayout * QDEOpenBoxPanel::buildScrollBarLayout(QScrollBar * & sb)
{
	// constants definition
	const int minSize{ 10};
	const int maxSize{ 200 };
	const int defSize{ 100 };
	const int minWidth{ 150 };

	// create the scroll bar and the label
	sb = new QScrollBar;
	sb->setOrientation(Qt::Horizontal);
	sb->setRange(minSize, maxSize);
	sb->setValue(defSize);
	sb->setMinimumWidth(minWidth);
	sb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	QLabel * label{ new QLabel(QString::number(defSize)) };
	label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	// create the layout
	QHBoxLayout * layout{ new QHBoxLayout };
	layout->addWidget(sb);
	layout->addWidget(label);

	// connect the scroll bar to the label and to the solution
	connect(sb, &QScrollBar::valueChanged, label, static_cast<void(QLabel::*)(int)>(&QLabel::setNum));
	connect(sb, &QScrollBar::valueChanged, this, &QDESolutionPanel::parameterChanged);

	return layout;
}

void QDEOpenBoxPanel::updateVisualization(QDEAdapter const & de)
{
	// constants definition
	static QColor const boxColor(211, 203, 156);
	static QColor const backgroundColor(96, 96, 96);
	static double const bigOffset{ 25.0 };
	static double const smallOffset{ 10.0 };
	static double const bigSmallRatio{ 3.0 };

	// process dimensions for all boxes drawing
	QSize const labelImageSize(mVisualizationLabel->size().width() - 1, mVisualizationLabel->size().height() - 1);
	double const smallGridCount{ std::ceil(std::sqrt(de.actualPopulation().size() - 1)) };
	double const hRatio{ (labelImageSize.width() - (smallGridCount + 1) * smallOffset) / smallGridCount };
	double const vRatio{ (labelImageSize.height() - smallGridCount * smallOffset - 2.0 * bigOffset) / (smallGridCount + bigSmallRatio) };
	double const imageSize{ std::min(hRatio, vRatio) };
	double const bigImageSize{ imageSize * bigSmallRatio };
	double const smallImageSize{ imageSize };
	QPointF const bigImageCenter(labelImageSize.width() / 2.0, bigOffset + bigImageSize / 2.0);
	QPointF const smallUpperLeftImageCenter(labelImageSize.width() / 2.0 - (smallGridCount - 1.0) / 2.0 * (smallImageSize + smallOffset), 2.0 * bigOffset + bigImageSize + smallImageSize / 2.0);

	// create the pixmap, the painter and fill the background
	QPixmap pixmap(labelImageSize);
	pixmap.fill(backgroundColor);
	QPainter painter(&pixmap);
	painter.setPen(Qt::NoPen);
	painter.setBrush(boxColor);

	// draw all boxes
	drawBox(painter, bigImageCenter, bigImageSize, de.actualPopulation()[0][0]);
	for (size_t i{ 1 }; i < de.actualPopulation().size(); ++i) {
		size_t row{ (i - 1) / static_cast<size_t>(smallGridCount) };
		size_t column{ (i - 1) % static_cast<size_t>(smallGridCount) };
		QPointF rowColOffset(column * (smallImageSize + smallOffset), row * (smallImageSize + smallOffset));
		drawBox(painter, smallUpperLeftImageCenter + rowColOffset, smallImageSize, de.actualPopulation()[i][0]);
	}

	// update the label
	mVisualizationLabel->setPixmap(pixmap);
}

void QDEOpenBoxPanel::drawBox(QPainter & painter, QPointF const & boxCenterPos, double boxSize, double cutSize)
{
	// polygon static definition
	static QPolygonF polygon(12);
	
	// process each dimensions required to create the polygon
	double const width{ boxWidth() };
	double const height{ boxHeight() };
	double const scale{ boxSize / std::max(width, height) };
	double const scaledWidth{ width * scale };
	double const scaledHeight{ height * scale };
	double const scaledCutSize{ cutSize * scale };
	double const halfScaledWidth{ scaledWidth / 2.0 };
	double const halfScaledHeight{ scaledHeight / 2.0 };

	// polygon formation representing the box
	polygon[ 0] = QPointF(-halfScaledWidth, -halfScaledHeight + scaledCutSize);
	polygon[ 1] = QPointF(-halfScaledWidth + scaledCutSize, -halfScaledHeight + scaledCutSize);
	polygon[ 2] = QPointF(-halfScaledWidth + scaledCutSize, -halfScaledHeight);
	polygon[ 3] = QPointF(-polygon[2].x(),  polygon[2].y());
	polygon[ 4] = QPointF(-polygon[1].x(),  polygon[1].y());
	polygon[ 5] = QPointF(-polygon[0].x(),  polygon[0].y());
	polygon[ 6] = QPointF( polygon[5].x(), -polygon[5].y());
	polygon[ 7] = QPointF( polygon[4].x(), -polygon[4].y());
	polygon[ 8] = QPointF( polygon[3].x(), -polygon[3].y());
	polygon[ 9] = QPointF(-polygon[8].x(),  polygon[8].y());
	polygon[10] = QPointF(-polygon[7].x(),  polygon[7].y());
	polygon[11] = QPointF(-polygon[6].x(),  polygon[6].y());

	// draw the box
	painter.save();
	painter.translate(boxCenterPos);
	painter.drawPolygon(polygon);
	painter.restore();
}









#include <OptimizationMaximization.h>
#include <FitnessIdentity.h>
#include <format>


static const std::string obp_title("Boîte ouverte");
static const std::string obp_summary("<p>Le problème de la boîte ouverte consiste à déterminer la taille de la coupe au quatre coins d'une surface rectangulaire permettant d'optimizer le volume de la boîte issue du pliage de cette feuille.</p>");
static const std::string obp_description(R".(<p>Ce problème se résoud dans un espace à une dimension, représantant la taille de la coupe 'cut' au quatre coins de la surface rectangulaire.</p>

<p>Le domaine de cette dimension correspond aux tailles possible de la coupe. Elle doit être comprise entre 0 et la moitié de la plus petite dimension de la surface rectangulaire. Théoriquement, les bornes devraient être excluses c = ]0, min(width, height) / 2[.</p>

<p>La fonction objective est le volume de la boîte issue de la coupe.<br/>
f(cut) = (width - 2 * cut) * (height - 2 * cut) * cut</p>).");


QDEOpenBoxPanel::OpenBoxStrategy::OpenBoxStrategy(double width, double height)
	: SolutionStrategy(obp_title, obp_summary, obp_description)
	, mWidth{ width }
	, mHeight{ height }
{
	// domain definition
	mSolutionDomain.resize(1);
	mSolutionDomain[0].set(0.0, std::min(height, width) / 2.0);
	
	// strategies definition
	setOptimizationStrategy(new de::OptimizationMaximization);
	setFitnessStrategy(new de::FitnessIdentity);
}

std::string QDEOpenBoxPanel::OpenBoxStrategy::toString(de::Solution const & solution) const
{
	// return the solution as a formatted string
	return std::format(R"...(
Taille de la feuille : {} x {}
Taille de la coupe   : {:0.6f} x {:0.6f}
Volume de la boite   : {:0.6f})...", mWidth, mHeight, solution[0], solution[0], solution.fitness());
}

double QDEOpenBoxPanel::OpenBoxStrategy::process(de::Solution const & solution)
{
	// assign a local variable for the cut size - only for readability
	double cut{ solution[0] };

	// validate if the solution is inside the domain
	if (!mSolutionDomain[0].validate(cut)) {
		return 0.0;
	}

	// process the volume of the box
	return cut * (mWidth - 2.0 * cut) * (mHeight - 2.0 * cut);
}

