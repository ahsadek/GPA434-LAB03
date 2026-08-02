#include "QDEPeakPanel.h"


#include <PeakFunctionMinSolution.h>
#include <PeakFunctionMaxSolution.h>
#include <PeakFunctionMinMaxSolution.h>

#include <QSurfaceDataArray>
#include <QCustom3DVolume>

#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QRadioButton>
#include <QFormLayout>
#include <QHBoxLayout>

#include <Q3DCamera>


// define the static constants
const size_t QDEPeakPanel::sXRes{ 49 };
const size_t QDEPeakPanel::sZRes{ sXRes };
const qreal QDEPeakPanel::sXMin{ -3.0 };
const qreal QDEPeakPanel::sXMax{ 3.0 };
const qreal QDEPeakPanel::sZMin{ -3.0 };
const qreal QDEPeakPanel::sZMax{ 3.0 };
const QString QDEPeakPanel::sInternalResourceMeshFileName(":/DEApplication/point");
const QString QDEPeakPanel::sExternalResourceMeshFileName("point.obj");
const QString QDEPeakPanel::sParametersTitle("Paramètres");
const QString QDEPeakPanel::sVisualizationTitle("Visualisation");
const QColor QDEPeakPanel::sMinColor(0xff, 0xbb, 0x00);
const QColor QDEPeakPanel::sMaxColor(0xff, 0x00, 0xbb);
const qreal QDEPeakPanel::sMeshOffset{ 0.25 };
const qreal QDEPeakPanel::sMeshScale{ 0.005 };
const float QDEPeakPanel::sAutoRotateSpeed{ 0.25f };



QDEPeakPanel::QDEPeakPanel(QWidget *parent)
	: QDESolutionPanel(parent)
	, mMinPeakRadio{ new QRadioButton }
	, mMaxPeakRadio{ new QRadioButton }
	, mMinMaxPeakRadio{ new QRadioButton }
	, mSurface{ new Q3DSurface }
	, mSurfaceWidget{ QWidget::createWindowContainer(mSurface) }
	, mMeshFileName()
	, mMeshAvailable{}
	, mMinColor(1, 1, QImage::Format_RGB32)
	, mMaxColor(1, 1, QImage::Format_RGB32)
{
	setupMeshElements();
	setupSurface();

	setupGUI();
	assemblingAndLayouting();
	establishConnections();
}

void QDEPeakPanel::rotateCamera()
{
	float rotation{ mSurface->scene()->activeCamera()->xRotation() + sAutoRotateSpeed };
	if (rotation >= 360.0f) rotation -= 360.0f;
	mSurface->scene()->activeCamera()->setXRotation(rotation);
}

de::SolutionStrategy * QDEPeakPanel::buildSolution() const
{
	switch (currentMode()) {
		case PeakMode::Minimum:
			return new de::PeakFunctionMinSolution;
		case PeakMode::Maximum:
			return new de::PeakFunctionMaxSolution;
		case PeakMode::MinMax:
		default:
			return new de::PeakFunctionMinMaxSolution;
	}
}

QDEPeakPanel::PeakMode QDEPeakPanel::currentMode() const
{
	if (mMinPeakRadio->isChecked()) {
		return PeakMode::Minimum;
	}

	if (mMaxPeakRadio->isChecked()) {
		return PeakMode::Maximum;
	}

	return PeakMode::MinMax;
}

void QDEPeakPanel::updateVisualization(QDEAdapter const & de)
{
	if (mMeshAvailable) {
		// Approche VRAIMENT inefficace => to do => doit réutiliser les points existants si la population ne change pas
		mSurface->removeCustomItems();

		switch (currentMode()) {
			case PeakMode::Minimum:
				for (size_t i{}; i < de.actualPopulation().size(); ++i) {
					addPoint(de.actualPopulation()[i][0], de.actualPopulation()[i][1], false);
				}
				break;
			case PeakMode::Maximum:
				for (size_t i{}; i < de.actualPopulation().size(); ++i) {
					addPoint(de.actualPopulation()[i][0], de.actualPopulation()[i][1], true);
				}
				break;
			case PeakMode::MinMax:
			default:
				for (size_t i{}; i < de.actualPopulation().size(); ++i) {
					addPoint(de.actualPopulation()[i][0], de.actualPopulation()[i][1], true);
					addPoint(de.actualPopulation()[i][2], de.actualPopulation()[i][3], false);
				}
				break;
		}
	}
}

void QDEPeakPanel::addPoint(qreal x, qreal z, bool maximumPoint)
{
	addPoint(x, de::PeakFunctionSolution::peak(x, z), z, maximumPoint);
}

void QDEPeakPanel::addPoint(qreal x, qreal y, qreal z, bool maximumPoint)
{
	QCustom3DItem * point{ new QCustom3DItem };
	point->setMeshFile(mMeshFileName);

	point->setTextureImage(maximumPoint ? mMaxColor : mMinColor);

	point->setPosition(QVector3D(z, y + sMeshOffset, x));
	point->setScaling(QVector3D(sMeshScale, sMeshScale, sMeshScale));

	mSurface->addCustomItem(point);
}

void QDEPeakPanel::setupMeshElements()
{
	QFile internalResourceFile(sInternalResourceMeshFileName);
	if (internalResourceFile.exists()) {
		mMeshFileName = sInternalResourceMeshFileName;
	}
	if (mMeshFileName.isEmpty()) {
		QFile externalResourceFile(sExternalResourceMeshFileName);
		if (externalResourceFile.exists()) {
			mMeshFileName = sExternalResourceMeshFileName;
		}
	}
	mMeshAvailable = !mMeshFileName.isEmpty();

	mMinColor.fill(sMinColor);
	mMaxColor.fill(sMaxColor);
}

void QDEPeakPanel::setupSurface()
{
	mSurface->axisX()->setTitle("x value");
	mSurface->axisY()->setTitle("z value");
	mSurface->axisZ()->setTitle("y value");
	mSurface->axisX()->setTitleVisible(true);
	mSurface->axisY()->setTitleVisible(true);
	mSurface->axisZ()->setTitleVisible(true);
	mSurface->axisX()->setAutoAdjustRange(true);
	mSurface->axisY()->setAutoAdjustRange(true);
	mSurface->axisZ()->setAutoAdjustRange(true);
	mSurface->axisX()->setLabelAutoRotation(90.0f);
	mSurface->axisY()->setLabelAutoRotation(90.0f);
	mSurface->axisZ()->setLabelAutoRotation(90.0f);
	mSurface->axisX()->setSegmentCount(6);
	mSurface->axisY()->setSegmentCount(10);
	mSurface->axisZ()->setSegmentCount(6);
	mSurface->axisX()->setSubSegmentCount(1);
	mSurface->axisY()->setSubSegmentCount(1);
	mSurface->axisZ()->setSubSegmentCount(1);
	mSurface->axisX()->setRange(sXMin, sXMax);
	mSurface->axisZ()->setRange(sZMin, sZMax);
	mSurface->axisY()->setRange(-10.0f, 10.0f);
	QSurfaceDataArray* data{ new QSurfaceDataArray };
	data->reserve(sXRes);
	for (size_t x{}; x < sXRes; ++x) {
		double xVal{ sXMin + (sXMax - sXMin) / double(sXRes - 1) * double(x) };
		QSurfaceDataRow* dataRow{ new QSurfaceDataRow(sZRes) };
		for (size_t z{}; z < sZRes; ++z) {
			double zVal{ sZMin + (sZMax - sZMin) / double(sZRes - 1) * double(z) };
			(*dataRow)[z].setPosition(QVector3D(zVal, de::PeakFunctionSolution::peak(xVal, zVal), xVal));
		}
		*data << dataRow;
	}

	QSurface3DSeries* peakFunc{ new QSurface3DSeries };
	peakFunc->dataProxy()->resetArray(data);
	mSurface->addSeries(peakFunc);
	mSurface->scene()->activeCamera()->setYRotation(35.0);
}

void QDEPeakPanel::setupGUI()
{
	mMinMaxPeakRadio->setChecked(true);
}

void QDEPeakPanel::assemblingAndLayouting()
{
	int const spacing{ 25 };
	QGroupBox* parametersGroupBox{ new QGroupBox(sParametersTitle) };
    QHBoxLayout * parametersLayout{ new QHBoxLayout(parametersGroupBox) };
	parametersLayout->addWidget( new QLabel("Point minimum") );
	parametersLayout->addWidget(mMinPeakRadio);
	parametersLayout->addSpacing(spacing);
	parametersLayout->addWidget( new QLabel("Point maximum") );
	parametersLayout->addWidget(mMaxPeakRadio);
	parametersLayout->addSpacing(spacing);
	parametersLayout->addWidget( new QLabel("Points min et max") );
	parametersLayout->addWidget(mMinMaxPeakRadio);
	parametersLayout->addSpacing(spacing);
	parametersLayout->addStretch();

	QGroupBox* visualizationGroupBox{ new QGroupBox(sVisualizationTitle) };
	QVBoxLayout* visualizationLayout{ new QVBoxLayout };
	visualizationLayout->addWidget(mSurfaceWidget);
	visualizationGroupBox->setLayout(visualizationLayout);
	mSurfaceWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout* layout{ new QVBoxLayout(this) };
	layout->addWidget(parametersGroupBox);
	layout->addWidget(visualizationGroupBox);
}

void QDEPeakPanel::establishConnections()
{
	connect(mMinPeakRadio, &QRadioButton::clicked, this, &QDESolutionPanel::parameterChanged);
	connect(mMaxPeakRadio, &QRadioButton::clicked, this, &QDESolutionPanel::parameterChanged);
	connect(mMinMaxPeakRadio, &QRadioButton::clicked, this, &QDESolutionPanel::parameterChanged);

	// Connect le signal 'timeout' du 'timer' de l'auto-rotation de la caméra.
	QObject::connect(&mAutoRotateTimer, &QTimer::timeout, this, &QDEPeakPanel::rotateCamera);
	// Démarre l'auto-rotation
	mAutoRotateTimer.start(30);
}

