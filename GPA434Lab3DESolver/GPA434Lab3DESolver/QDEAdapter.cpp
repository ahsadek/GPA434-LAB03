#include "QDEAdapter.h"


QDEAdapter::QDEAdapter(QObject *parent)
	: QObject(parent)
{
}

bool QDEAdapter::isReady()
{
	return mDE.isReady();
}

size_t QDEAdapter::currentGeneration() const
{
	return mDE.currentGeneration();
}

bool QDEAdapter::isStoppingCriteriaReached() const
{
	return mDE.isStoppingCriteriaReached();
}

de::DifferentialEvolution::SetupState QDEAdapter::setup(de::SolutionStrategy * solution)
{
	return mDE.setup(solution);
}

de::SolutionStrategy const & QDEAdapter::solution()
{
	return mDE.solution();
}

QString QDEAdapter::bestSolutionInfo() const
{
	return QString::fromStdString(mDE.bestSolutionInfo());
}

de::History const & QDEAdapter::statisticsHistory() const
{
	return mDE.statisticsHistory();
}

de::Population QDEAdapter::actualPopulation() const
{
	return mDE.actualPopulation();
}

void QDEAdapter::setEngineParameters(de::EngineParameters const& parameters)
{
	mDE.setEngineParameters(parameters);
}

void QDEAdapter::stepEvolution()
{
	if (!isReady()) {
		return;
	}

	if (!mDE.isStoppingCriteriaReached()) {
		mDE.processToNextGeneration();
		emit oneEvolutionStepped();
	}

	if (mDE.isStoppingCriteriaReached()) {
		emit stoppingCriteriaReached();
	}
}

void QDEAdapter::reset()
{
	mDE.reset();
	emit wasReset();
}


