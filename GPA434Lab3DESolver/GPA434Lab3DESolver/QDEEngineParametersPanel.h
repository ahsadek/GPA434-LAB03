#pragma once


#include <unordered_map>
#include <QGroupBox>
#include <QComboBox>
#include <EngineParameters.h>

class QSpinBox;
class QScrollBar;
class QLabel;

#include "QDEAdapter.h"
#include <InitializationStrategy.h>
#include <MutationStrategy.h>
#include <MutationStrategy.h>
#include <CrossoverStrategy.h>
#include <CrossoverStrategy.h>
#include <SelectionStrategy.h>


//! \brief Panneau affichant les paramètres génériques du moteur d'évolution différentielle.
class QDEEngineParametersPanel : public QGroupBox
{
	Q_OBJECT

public:
	QDEEngineParametersPanel(QDEAdapter const& deAdapter, QWidget * parent = nullptr);
	QDEEngineParametersPanel(QDEEngineParametersPanel const &) = default;
	QDEEngineParametersPanel(QDEEngineParametersPanel &&) = default;
	QDEEngineParametersPanel& operator=(QDEEngineParametersPanel const &) = default;
	QDEEngineParametersPanel& operator=(QDEEngineParametersPanel &&) = default;
	~QDEEngineParametersPanel() override = default;

	de::EngineParameters parameters() const;
	
	void addInitializationStrategy(de::InitializationStrategy * prototype);
	void addAdaptiveDomainStrategy(de::AdaptiveDomainStrategy* prototype);
	void addMutationStrategy(de::MutationStrategy* prototype);
	void addCrossoverStrategy(de::CrossoverStrategy * prototype);
	void addSelectionStrategy(de::SelectionStrategy * prototype);
	void addStoppingCriteriaStrategy(de::StoppingCriteriaStrategy * prototype);

public slots:
	void setParameters(de::EngineParameters const& parameters);
	void setParametersFromSolution(de::SolutionStrategy const* solution);
	void enable();
	void disable();

signals:
	void parameterChanged(de::EngineParameters const & parameters);

private slots:
	void changeParameters();

private:
	QDEAdapter const& mDEAdapter;
	QSpinBox * mPopulationSize{};
	QSpinBox * mGenerationCount{};
	QComboBox * mInitializationStrategyComboBox{};
	QComboBox * mAdaptiveDomainStrategyComboBox{};
	QComboBox * mMutationStrategyComboBox{};
	QScrollBar* mMutationStrategyValue{};
	QLabel* mMutationStrategyLabel{};
	QComboBox * mCrossoverStrategyComboBox{};
	QScrollBar* mCrossoverRateValue{};
	QLabel* mCrossoverRateLabel{};
	QComboBox * mSelectionStrategyComboBox{};
	QComboBox * mStoppingCriteriaComboBox{};

	template <typename T>
	using StrategyContainer = std::unordered_map<std::string, std::unique_ptr<T>>;
	StrategyContainer<de::InitializationStrategy> mInitializationPrototypes;
	StrategyContainer<de::AdaptiveDomainStrategy> mAdaptiveDomainPrototypes;
	StrategyContainer<de::MutationStrategy> mMutationPrototypes;
	StrategyContainer<de::CrossoverStrategy> mCrossoverPrototypes;
	StrategyContainer<de::SelectionStrategy> mSelectionPrototypes;
	StrategyContainer<de::StoppingCriteriaStrategy> mStoppingCriteriaPrototypes;

	void setupGUI();
	void assemblingAndLayouting();
	void establishConnections();

	bool isReady() const;

	template <typename T>
	void addStrategy(T* prototype, StrategyContainer<T>& container, QComboBox* comboBox);
	template <typename T>
	T* getClonedStrategy(StrategyContainer<T> const& container, QComboBox const* comboBox) const;

};



#include "QDEEngineParametersPanel.h"





