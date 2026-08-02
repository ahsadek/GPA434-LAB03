#pragma once


#include <QTabWidget>
#include <SolutionStrategy.h>

class QDESolutionPanel;


#include "QDEAdapter.h"


//! \brief Panneau supervisant toutes les solutions insérées dans l'application.
class QDESolutionTabPanel : public QTabWidget
{
	Q_OBJECT

public:
	QDESolutionTabPanel(QDEAdapter const& de, QWidget * parent = nullptr);
	QDESolutionTabPanel(QDESolutionTabPanel const &) = default;
	QDESolutionTabPanel(QDESolutionTabPanel &&) = default;
	QDESolutionTabPanel& operator=(QDESolutionTabPanel const &) = default;
	QDESolutionTabPanel& operator=(QDESolutionTabPanel &&) = default;
	~QDESolutionTabPanel() = default;

	void addSolutionPanel(QDESolutionPanel * dESolutionPanel);

signals:
	void solutionChanged(de::SolutionStrategy* solution);

public slots:
	void enable();
	void disable();
	void updateVisualization();

private slots:
	void changeSolution();

private:
	QDEAdapter const& mDEAdapter;

	using QTabWidget::addTab;

	class InternalSolutionPanel : public QWidget
	{
	public:
		InternalSolutionPanel(QDESolutionPanel* dESolutionPanel, de::SolutionStrategy const & strategy);
		de::SolutionStrategy* buildSolution() const;
		void updateVisualization(QDEAdapter const& mDE);

	private:
		QDESolutionPanel* mDESolutionPanel;
	};
};
