#include "QDEHistoryChartPanel.h"


#include "QDEAdapter.h"
#include <QValueAxis>


QDEHistoryChartPanel::QDEHistoryChartPanel(QDEAdapter const& de, QWidget* parent)
	: QChartView(parent)
	, mDEAdapter{ de }
	, mChart{ new QChart }
	, mBestData{ new QLineSeries }
	, mMedianData{ new QLineSeries }
	, mWorstData{ new QLineSeries }
{
	setupGUI();
	assemblingAndLayouting();
	establishConnections();
}

void QDEHistoryChartPanel::updateHistory()
{
	mBestData->append(mBestData->count(), mDEAdapter.statisticsHistory().last().bestSolution().fitness());
	mMedianData->append(mMedianData->count(), mDEAdapter.statisticsHistory().last().medianSolution().fitness());
	mWorstData->append(mWorstData->count(), mDEAdapter.statisticsHistory().last().worstSolution().fitness());

	double xMin, xMax, yMin, yMax;
	mDEAdapter.statisticsHistory().getRange(xMin, xMax, yMin, yMax);
	mChart->axes(Qt::Horizontal)[0]->setRange(xMin, xMax);
	//mChart->axes(Qt::Horizontal)[0]->setRange(xMin + 1.0, xMax + 1.0);
	mChart->axes(Qt::Vertical)[0]->setRange(yMin, yMax);
}

void QDEHistoryChartPanel::reset()
{
	mBestData->clear();
	mMedianData->clear();
	mWorstData->clear();
	mChart->axes(Qt::Horizontal)[0]->setRange(0.0, 1.0);
	mChart->axes(Qt::Vertical)[0]->setRange(0.0, 1.0);
}

void QDEHistoryChartPanel::setupGUI()
{
	mChart->legend()->hide();
	mChart->addSeries(mMedianData);
	mChart->addSeries(mBestData);
	mChart->addSeries(mWorstData);
	mChart->createDefaultAxes();
	mChart->setTitle("Évolution");
	mChart->axes(Qt::Horizontal)[0]->setTitleText("Génération");
	mChart->axes(Qt::Vertical)[0]->setTitleText("'Fitness'");

	static_cast<QValueAxis*>(mChart->axes(Qt::Horizontal)[0])->setLabelFormat("%i");

	mBestData->setColor(QColor(128, 128, 255));
	mMedianData->setColor(QColor(196, 196, 255));
	mWorstData->setColor(QColor(222, 196, 255));

	setChart(mChart);
	setRenderHint(QPainter::Antialiasing);
}

void QDEHistoryChartPanel::assemblingAndLayouting()
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void QDEHistoryChartPanel::establishConnections()
{
	connect(&mDEAdapter, &QDEAdapter::oneEvolutionStepped, this, &QDEHistoryChartPanel::updateHistory);
	connect(&mDEAdapter, &QDEAdapter::wasReset, this, &QDEHistoryChartPanel::reset);
}




