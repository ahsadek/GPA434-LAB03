#pragma once

#include <QGroupBox>
#include <QTimer>
#include "QDEAdapter.h"

class QPushButton;
class QSlider;
class QLabel;


//! \brief Panneau permettant le contrôle de la simulation.
class QDEControllerPanel : public QGroupBox
{
	Q_OBJECT

public:
	QDEControllerPanel(QDEAdapter const & dEAdapter, QWidget * parent = nullptr);
	QDEControllerPanel(QDEControllerPanel const &) = default;
	QDEControllerPanel(QDEControllerPanel &&) = default;
	QDEControllerPanel& operator=(QDEControllerPanel const &) = default;
	QDEControllerPanel& operator=(QDEControllerPanel &&) = default;
	~QDEControllerPanel() override = default;

signals:
	void evolutionRequired();
	void resetRequired();
	void evolutionStarted();
	void evolutionStopped();

public slots:
	void startSimulation();
	void stopSimulation();
	void resetSimulation();

private slots:
	void toggleStartStopSimulation();
	void updateGui();
	void updateSpeed();
	void updateCurrentGeneration();

private:
	QDEAdapter const & mDEAdapter;

	QPushButton * mStepButton{};
	QPushButton * mResetButton{};
	QPushButton * mStartButton{};
	QSlider * mSpeedSlider{};
	QLabel * mSpeedLabel{};
	QLabel * mCurrentGenerationLabel{};
	
	QTimer mSimulationTimer;
	qreal getTimerValue();

	void setupGUI();
	void assemblingAndLayouting();
	void establishConnections();

	static const qreal mSlowerTimeout;
	static const size_t mMinimumSpeedRange;
	static const size_t mMaximumSpeedRange;
	static const size_t mDefaultSpeedRange;
};
