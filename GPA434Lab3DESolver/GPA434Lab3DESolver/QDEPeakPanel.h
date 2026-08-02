#pragma once


#include "QDESolutionPanel.h"
#include <QtDataVisualization>
#include <Q3DSurface>
#include <QTimer>


class QRadioButton;


//! \brief Panneau représentant spécifiquement le problème d'identification 
//! des extrema de la fonction `Peak` de `Matlab`.
class QDEPeakPanel : public QDESolutionPanel
{
	Q_OBJECT

public:
	QDEPeakPanel(QWidget * parent = nullptr);
	QDEPeakPanel(QDEPeakPanel const &) = default;
	QDEPeakPanel(QDEPeakPanel &&) = default;
	QDEPeakPanel& operator=(QDEPeakPanel const &) = default;
	QDEPeakPanel& operator=(QDEPeakPanel &&) = default;
	~QDEPeakPanel() override = default;

	de::SolutionStrategy * buildSolution() const override;

	enum PeakMode { Minimum, Maximum, MinMax };
	PeakMode currentMode() const;

public slots:
	void updateVisualization(QDEAdapter const & de) override;

private slots:
	void rotateCamera();

private:
	QRadioButton * mMinPeakRadio{};
	QRadioButton * mMaxPeakRadio{};
	QRadioButton * mMinMaxPeakRadio{};

	Q3DSurface * mSurface{};
	QWidget * mSurfaceWidget{};
	QString mMeshFileName;
	bool mMeshAvailable;
	QImage mMinColor;
	QImage mMaxColor;
	QTimer mAutoRotateTimer;

	static const size_t sXRes, sZRes;
	static const qreal sXMin, sXMax, sZMin, sZMax;
	static const QString sInternalResourceMeshFileName;
	static const QString sExternalResourceMeshFileName;
	static const QString sParametersTitle, sVisualizationTitle;//, sDescription
	static const QColor sMinColor, sMaxColor;
	static const qreal sMeshOffset;
	static const qreal sMeshScale;
	static const float sAutoRotateSpeed;

	void addPoint(qreal x, qreal z, bool maximumPoint);
	void addPoint(qreal x, qreal y, qreal z, bool maximumPoint);

	void setupMeshElements();
	void setupSurface();

	void setupGUI();
	void assemblingAndLayouting();
	void establishConnections();
};
