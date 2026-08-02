#pragma once

#include "QDEEngineParametersPanel.h"


#include <QSpinBox>
#include <QComboBox>
#include <QScrollBar>
#include <QLabel>
#include <QFormLayout>

#include <EngineParameters.h>
#include <SolutionStrategy.h>

#include <InitializationBySolution.h>
#include <InitializationDomainUniform.h>
#include <AdaptiveDomainNoConstraint.h>
#include <AdaptiveDomainClamped.h>
#include <MutationRand1.h>
#include <MutationBest1.h>
#include <CrossoverBinomial.h>
#include <CrossoverExponential.h>
#include <SelectionBestFitness.h>


template <typename T>
void QDEEngineParametersPanel::addStrategy(T* prototype, StrategyContainer<T>& container, QComboBox* comboBox) {
	if (prototype) {
		if (container.find(prototype->name()) != container.end()) { throw std::invalid_argument("Prototype's name already exist."); }
		container[prototype->name()] = std::unique_ptr<T>(prototype);
		comboBox->addItem(QString::fromStdString(prototype->name()));
	}
}
template <typename T>
T* QDEEngineParametersPanel::getClonedStrategy(StrategyContainer<T> const& container, QComboBox const* comboBox) const {
	return static_cast<T*>(container.find(comboBox->currentText().toStdString())->second->clone());
}

QDEEngineParametersPanel::QDEEngineParametersPanel(QDEAdapter const& deAdapter, QWidget * parent)
	: QGroupBox("Paramètres de l'engin d'évolution différentielle", parent)
	, mDEAdapter{ deAdapter }
	, mPopulationSize{ new QSpinBox }
	, mGenerationCount{ new QSpinBox }
	, mInitializationStrategyComboBox{ new QComboBox }
	, mAdaptiveDomainStrategyComboBox{ new QComboBox }
	, mMutationStrategyComboBox{ new QComboBox }
	, mMutationStrategyValue{ new QScrollBar }
	, mMutationStrategyLabel{ new QLabel }
	, mCrossoverStrategyComboBox{ new QComboBox }
	, mCrossoverRateValue{ new QScrollBar }
	, mCrossoverRateLabel{ new QLabel }
	, mSelectionStrategyComboBox{ new QComboBox }
	, mStoppingCriteriaComboBox{ new QComboBox }
{
	establishConnections();
	setupGUI();
	assemblingAndLayouting();

	addInitializationStrategy(new de::InitializationBySolution);
	addInitializationStrategy(new de::InitializationDomainUniform);
	addAdaptiveDomainStrategy(new de::AdaptiveDomainNoConstraint);
	addAdaptiveDomainStrategy(new de::AdaptiveDomainClamped);
	addMutationStrategy(new de::MutationBest1);
	addMutationStrategy(new de::MutationRand1);
	addCrossoverStrategy(new de::CrossoverBinomial);
	addCrossoverStrategy(new de::CrossoverExponential);
	addSelectionStrategy(new de::SelectionBestFitness);

	connect(this, &QDEEngineParametersPanel::parameterChanged, &mDEAdapter, &QDEAdapter::setEngineParameters);
}

de::EngineParameters QDEEngineParametersPanel::parameters() const
{
	de::EngineParameters param;

	if (!isReady()) {
		return param;
	}

	param.setPopulationSize(mPopulationSize->value());
	param.setMaxGeneration(mGenerationCount->value());

	param.setInitializationStrategy(getClonedStrategy(mInitializationPrototypes, mInitializationStrategyComboBox));
	param.setAdaptiveDomainStrategy(getClonedStrategy(mAdaptiveDomainPrototypes, mAdaptiveDomainStrategyComboBox));
	param.setMutationStrategy(getClonedStrategy(mMutationPrototypes, mMutationStrategyComboBox));
	param.setMutationFactor(mMutationStrategyValue->value() / 100.0);
	param.setCrossoverStrategy(getClonedStrategy(mCrossoverPrototypes, mCrossoverStrategyComboBox));
	param.setCrossoverRate(mCrossoverRateValue->value() / 100.0);
	param.setSelectionStrategy(getClonedStrategy(mSelectionPrototypes, mSelectionStrategyComboBox));

	int index{ mStoppingCriteriaComboBox->currentData().toInt() };
	if (index > 0) {
		param.clearStoppingCriteraStrategy();
		param.addStoppingCriteriaStrategy(getClonedStrategy(mStoppingCriteriaPrototypes, mStoppingCriteriaComboBox));
	}

	return param;
}

void QDEEngineParametersPanel::setParameters(de::EngineParameters const& parameters)
{
	if (parameters.isReady()) {
		mPopulationSize->setValue(parameters.populationSize());
		mGenerationCount->setValue(parameters.maximumGeneration());

		auto setComboNameIfExist{ [](de::Strategy* strategy, QComboBox* combo) {
				int index{ combo->findText(QString::fromStdString(strategy->name())) };
				if (index >= 0) combo->setCurrentIndex(index);
			} };
		
		setComboNameIfExist(parameters.initializationStrategy(), mInitializationStrategyComboBox);
		setComboNameIfExist(parameters.adaptiveDomainStrategy(), mAdaptiveDomainStrategyComboBox);
		setComboNameIfExist(parameters.mutationStrategy(), mMutationStrategyComboBox);
		mMutationStrategyValue->setValue(static_cast<int>(parameters.mutationFactor() * 100.0));
		setComboNameIfExist(parameters.crossoverStrategy(), mCrossoverStrategyComboBox);
		mCrossoverRateValue->setValue(static_cast<int>(parameters.crossoverRate() * 100.0));
		setComboNameIfExist(parameters.selectionStrategy(), mSelectionStrategyComboBox);

		// TODO: Stopping criteria
	}
}

void QDEEngineParametersPanel::addInitializationStrategy(de::InitializationStrategy* prototype)
{
	addStrategy(prototype, mInitializationPrototypes, mInitializationStrategyComboBox);
}

void QDEEngineParametersPanel::addAdaptiveDomainStrategy(de::AdaptiveDomainStrategy* prototype)
{
	addStrategy(prototype, mAdaptiveDomainPrototypes, mAdaptiveDomainStrategyComboBox);
}

void QDEEngineParametersPanel::addMutationStrategy(de::MutationStrategy* prototype)
{
	addStrategy(prototype, mMutationPrototypes, mMutationStrategyComboBox);
}

void QDEEngineParametersPanel::addCrossoverStrategy(de::CrossoverStrategy* prototype)
{
	addStrategy(prototype, mCrossoverPrototypes, mCrossoverStrategyComboBox);
}

void QDEEngineParametersPanel::addSelectionStrategy(de::SelectionStrategy* prototype)
{
	addStrategy(prototype, mSelectionPrototypes, mSelectionStrategyComboBox);
}

void QDEEngineParametersPanel::addStoppingCriteriaStrategy(de::StoppingCriteriaStrategy* prototype)
{
	addStrategy(prototype, mStoppingCriteriaPrototypes, mStoppingCriteriaComboBox);
}

void QDEEngineParametersPanel::setParametersFromSolution(de::SolutionStrategy const * solution)
{
	if (solution) {
		setParameters(solution->engineParameters());
	}
}

void QDEEngineParametersPanel::enable()
{
	setEnabled(true);
}

void QDEEngineParametersPanel::disable()
{
	setEnabled(false);
}

void QDEEngineParametersPanel::setupGUI()
{
	mPopulationSize->setRange(de::EngineParameters::minimumPopulationSize(), de::EngineParameters::maximumPopulationSize());
	mPopulationSize->setValue(de::EngineParameters::defaultPopulationSize());
	mPopulationSize->setToolTip(QString("Détermine la taille de la population [" + QString::number(de::EngineParameters::minimumPopulationSize()) + ", " + QString::number(de::EngineParameters::maximumPopulationSize()) + "]."));

	mGenerationCount->setRange(de::EngineParameters::minimumGenerationCount(), de::EngineParameters::maximumGenerationCount());
	mGenerationCount->setValue(de::EngineParameters::defaultGenerationCount());
	mGenerationCount->setToolTip(QString("Détermine le nombre maximum de génération pour la simulation [" + QString::number(de::EngineParameters::minimumGenerationCount()) + ", " + QString::number(de::EngineParameters::maximumGenerationCount()) + "]."));

	mInitializationStrategyComboBox->setToolTip("Détermine la stratégie d'initialisation à utiliser pour la simulation.");
	mAdaptiveDomainStrategyComboBox->setToolTip("Détermine la stratégie de gestion de contrainte du domaine pendant l'évolution.");
	mMutationStrategyComboBox->setToolTip("Détermine la stratégie de mutation à utiliser pour la simulation.");

	int const labelSize{ 120 };
	mMutationStrategyLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	mMutationStrategyLabel->setMinimumWidth(labelSize);
	mMutationStrategyValue->setOrientation(Qt::Horizontal);
	mMutationStrategyValue->setRange(0, 200);
	mMutationStrategyValue->setValue(30);

	mCrossoverStrategyComboBox->setToolTip("Détermine la stratégie de croisement à utiliser pour la simulation.");

	mCrossoverRateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	mCrossoverRateLabel->setMinimumWidth(labelSize);
	mCrossoverRateValue->setOrientation(Qt::Horizontal);
	mCrossoverRateValue->setRange(0, 100);
	mCrossoverRateValue->setValue(80);

	mSelectionStrategyComboBox->setToolTip("Détermine la stratégie de sélection à utiliser pour la simulation.");

	mStoppingCriteriaComboBox->setEnabled(false);
	mStoppingCriteriaComboBox->addItem("No extra criteria", 0);
	mStoppingCriteriaComboBox->setToolTip("...not implemented yet...");
}

void QDEEngineParametersPanel::assemblingAndLayouting()
{
	QFormLayout* formLayout{ new QFormLayout(this) };
	formLayout->addRow("Taille de la population", mPopulationSize);
	formLayout->addRow("Nombre max. de génération", mGenerationCount);
	formLayout->addRow("Stratégie d'initialisation", mInitializationStrategyComboBox);
	formLayout->addRow("Stratégie contrainte domaine", mAdaptiveDomainStrategyComboBox);
	formLayout->addRow("Stratégie de mutation", mMutationStrategyComboBox);
	formLayout->addRow(mMutationStrategyLabel, mMutationStrategyValue);
	formLayout->addRow("Stratégie de croisement", mCrossoverStrategyComboBox);
	formLayout->addRow(mCrossoverRateLabel, mCrossoverRateValue);
	formLayout->addRow("Stratégie de sélection", mSelectionStrategyComboBox);
	formLayout->addRow("Critères d'arrêt", mStoppingCriteriaComboBox);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
}

void QDEEngineParametersPanel::establishConnections()
{
	connect(mMutationStrategyValue, &QScrollBar::valueChanged, [this](int value) { mMutationStrategyLabel->setText(QString("f : %1").arg((double)value / 100.0, 0, 'f', 2)); });
	connect(mMutationStrategyValue, &QScrollBar::valueChanged, this, &QDEEngineParametersPanel::changeParameters);
	connect(mCrossoverRateValue, &QScrollBar::valueChanged, [this](int value) { mCrossoverRateLabel->setText(QString("R : %1").arg((double)value / 100.0, 0, 'f', 2)); });
	connect(mCrossoverRateValue, &QScrollBar::valueChanged, this, &QDEEngineParametersPanel::changeParameters);

	connect(mPopulationSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mGenerationCount, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mInitializationStrategyComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mAdaptiveDomainStrategyComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mMutationStrategyComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mCrossoverStrategyComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QDEEngineParametersPanel::changeParameters);
	connect(mSelectionStrategyComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QDEEngineParametersPanel::changeParameters);
}

bool QDEEngineParametersPanel::isReady() const
{
	return mPopulationSize->value() >= 5 &&
		mGenerationCount->value() >= 3 &&
		mInitializationStrategyComboBox->currentText() != "" &&
		mAdaptiveDomainStrategyComboBox->currentText() != "" &&
		mMutationStrategyComboBox->currentText() != "" &&
		mCrossoverStrategyComboBox->currentText() != "" &&
		mSelectionStrategyComboBox->currentText() != "" &&
		mStoppingCriteriaComboBox->currentText() != "";
}

void QDEEngineParametersPanel::changeParameters()
{
	emit parameterChanged(parameters());
}


