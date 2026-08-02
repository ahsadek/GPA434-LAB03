#pragma once


#include <QChartView>
#include <QChart>
#include <QLineSeries>

class QDEAdapter;


//! \brief Panneau affichant l'historique de performance pendant l'évolution.
class QDEHistoryChartPanel : public QChartView
{
	Q_OBJECT

public:
	QDEHistoryChartPanel(QDEAdapter const& de, QWidget * parent = nullptr);
	QDEHistoryChartPanel(QDEHistoryChartPanel const &) = default;
	QDEHistoryChartPanel(QDEHistoryChartPanel &&) = default;
	QDEHistoryChartPanel& operator=(QDEHistoryChartPanel const &) = default;
	QDEHistoryChartPanel& operator=(QDEHistoryChartPanel &&) = default;
	~QDEHistoryChartPanel() override = default;

public slots:
	void updateHistory();
	void reset();

private:
	QDEAdapter const& mDEAdapter;
	QChart * mChart{};
	QLineSeries * mBestData{};
	QLineSeries * mMedianData{};
	QLineSeries * mWorstData{};

	void setupGUI();
	void assemblingAndLayouting();
	void establishConnections();
};
