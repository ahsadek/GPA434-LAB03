#include "QDEControllerPanel.h"


#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>


const qreal QDEControllerPanel::mSlowerTimeout{ 500.0 };
const size_t QDEControllerPanel::mMinimumSpeedRange{ 1 };
const size_t QDEControllerPanel::mMaximumSpeedRange{ 10 };
const size_t QDEControllerPanel::mDefaultSpeedRange{ 7 };


QDEControllerPanel::QDEControllerPanel(QDEAdapter const & dEAdapter, QWidget * parent)
	: QGroupBox("Contrôle de la simulation", parent)
	, mDEAdapter{ dEAdapter }
	, mStepButton{ new QPushButton("Un pas de simulation") }
	, mResetButton{ new QPushButton("Réinitialiser la simulation") }
	, mStartButton{ new QPushButton("Démarrer") }
	, mSpeedSlider{ new QSlider }
	, mSpeedLabel{ new QLabel(QString::number(mDefaultSpeedRange)) }
	, mCurrentGenerationLabel{ new QLabel("0") }
{
	setupGUI();
	assemblingAndLayouting();
	establishConnections();
}

void QDEControllerPanel::updateGui()
{
	mStepButton->setEnabled(!mSimulationTimer.isActive() && !mDEAdapter.isStoppingCriteriaReached());
	mResetButton->setEnabled(!mSimulationTimer.isActive());

	mStartButton->setEnabled(true);
	mSpeedSlider->setEnabled(true);

	mStartButton->setText(mSimulationTimer.isActive() ? "Arrêter" : "Démarrer");

	updateCurrentGeneration();
}

void QDEControllerPanel::updateSpeed()
{
	mSimulationTimer.setInterval(getTimerValue());
}

qreal QDEControllerPanel::getTimerValue()
{
	return (1.0 - static_cast<qreal>(mSpeedSlider->value()) / mSpeedSlider->maximum()) * mSlowerTimeout;
}

void QDEControllerPanel::setupGUI()
{
	mSpeedSlider->setRange(mMinimumSpeedRange, mMaximumSpeedRange);
	mSpeedSlider->setValue(mDefaultSpeedRange);
	mSpeedSlider->setOrientation(Qt::Horizontal);
	mSpeedSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	mCurrentGenerationLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}

void QDEControllerPanel::assemblingAndLayouting()
{
	QHBoxLayout* sliderLayout{ new QHBoxLayout };
	sliderLayout->addWidget(new QLabel("Vitesse de simulation"));
	sliderLayout->addWidget(mSpeedSlider);
	sliderLayout->addWidget(mSpeedLabel);

	QFrame* separatorFrame{ new QFrame };
	separatorFrame->setFrameStyle(QFrame::HLine | QFrame::Sunken);
	separatorFrame->setLineWidth(0);
	separatorFrame->setMidLineWidth(1);

	QHBoxLayout* currentGenerationLayout{ new QHBoxLayout };
	currentGenerationLayout->addWidget(new QLabel("Génération courante : "));
	currentGenerationLayout->addWidget(mCurrentGenerationLabel);
	currentGenerationLayout->addStretch();

	QHBoxLayout* stepResetButtonsLayout{ new QHBoxLayout };
	stepResetButtonsLayout->addWidget(mStepButton);
	stepResetButtonsLayout->addWidget(mResetButton);

	QVBoxLayout* boxLayout{ new QVBoxLayout };
	boxLayout->addLayout(stepResetButtonsLayout);
	boxLayout->addWidget(separatorFrame);
	boxLayout->addWidget(mStartButton);
	boxLayout->addLayout(sliderLayout);
	boxLayout->addLayout(currentGenerationLayout);
	boxLayout->addStretch();

	setLayout(boxLayout);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
}

void QDEControllerPanel::establishConnections()
{
	// evolutions
	connect(mStepButton, &QPushButton::pressed, this, &QDEControllerPanel::evolutionRequired);
	connect(mResetButton, &QPushButton::pressed, this, &QDEControllerPanel::resetSimulation);
	connect(mStartButton, &QPushButton::pressed, this, &QDEControllerPanel::toggleStartStopSimulation);

	connect(&mSimulationTimer, &QTimer::timeout, this, &QDEControllerPanel::evolutionRequired);
	connect(&mSimulationTimer, &QTimer::timeout, this, &QDEControllerPanel::updateCurrentGeneration);

	// gui
	connect(mSpeedSlider, &QSlider::valueChanged, mSpeedLabel, static_cast<void(QLabel::*)(int)>(&QLabel::setNum));
	connect(mSpeedSlider, &QSlider::valueChanged, this, &QDEControllerPanel::updateSpeed);
	connect(mStepButton, &QPushButton::pressed, this, &QDEControllerPanel::updateGui);
	connect(mResetButton, &QPushButton::pressed, this, &QDEControllerPanel::updateGui);
	connect(mStartButton, &QPushButton::pressed, this, &QDEControllerPanel::updateGui);

	// adapter connexions
	connect(this, &QDEControllerPanel::evolutionRequired, &mDEAdapter, &QDEAdapter::stepEvolution);
	connect(this, &QDEControllerPanel::resetRequired, &mDEAdapter, &QDEAdapter::reset);
	connect(&mDEAdapter, &QDEAdapter::stoppingCriteriaReached, this, &QDEControllerPanel::stopSimulation);
}

void QDEControllerPanel::updateCurrentGeneration()
{
	mCurrentGenerationLabel->setText(QString::number(mDEAdapter.currentGeneration()));
}

void QDEControllerPanel::startSimulation()
{
	mSimulationTimer.start(getTimerValue());
	emit evolutionStarted();
	updateGui();
}

void QDEControllerPanel::resetSimulation()
{
	emit resetRequired();
	updateGui();
}

void QDEControllerPanel::stopSimulation()
{
	mSimulationTimer.stop();
	emit evolutionStopped();
	updateGui();
}

void QDEControllerPanel::toggleStartStopSimulation()
{
	if (mDEAdapter.isStoppingCriteriaReached()) {
		resetSimulation();
	}

	if (mSimulationTimer.isActive()) {
		stopSimulation();
	} else {
		startSimulation();
	}
}
