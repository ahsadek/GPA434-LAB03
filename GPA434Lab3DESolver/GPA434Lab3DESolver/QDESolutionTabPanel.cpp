#include "QDESolutionTabPanel.h"

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QMessageBox>
#include "QDESolutionPanel.h"
#include "QElidedLabel.h"


QDESolutionTabPanel::QDESolutionTabPanel(QDEAdapter const& de, QWidget *parent)
	: QTabWidget(parent)
	, mDEAdapter{ de }
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	connect(this, &QTabWidget::currentChanged, this, &QDESolutionTabPanel::changeSolution);

	connect(&mDEAdapter, &QDEAdapter::oneEvolutionStepped, this, &QDESolutionTabPanel::updateVisualization);
	connect(&mDEAdapter, &QDEAdapter::wasReset, this, &QDESolutionTabPanel::updateVisualization);

	connect(this, &QDESolutionTabPanel::solutionChanged, &mDEAdapter, &QDEAdapter::setup);

}

void QDESolutionTabPanel::changeSolution()
{
	emit solutionChanged(static_cast<InternalSolutionPanel*>(currentWidget())->buildSolution());
}

void QDESolutionTabPanel::addSolutionPanel(QDESolutionPanel * dESolutionPanel)
{
	if (!dESolutionPanel) {
		throw std::runtime_error("QDESolutionTab::addSolutionPanel: dESolutionPanel is nullptr");
	}

	std::unique_ptr<de::SolutionStrategy> solution(dESolutionPanel->buildSolution());
	if (!solution) {
		QMessageBox::warning(this, "Error", "Invalid solution");
		return;
	}


	int index{ addTab(new InternalSolutionPanel(dESolutionPanel, *solution), QString::fromStdString(solution->name())) };

	connect(dESolutionPanel, &QDESolutionPanel::parameterChanged, this, &QDESolutionTabPanel::changeSolution);

	setCurrentIndex(index);
}

void QDESolutionTabPanel::enable()
{
	setEnabled(true);
}

void QDESolutionTabPanel::disable()
{
	setEnabled(false);
}

void QDESolutionTabPanel::updateVisualization()
{
	if (count() > 0) {
        static_cast<InternalSolutionPanel*>(currentWidget())->updateVisualization(mDEAdapter);
    }
}

QDESolutionTabPanel::InternalSolutionPanel::InternalSolutionPanel(QDESolutionPanel* dESolutionPanel, de::SolutionStrategy const& strategy)
	: mDESolutionPanel{ dESolutionPanel }
{
	QString strategyName(QString::fromStdString(strategy.name()));
	QString strategySummary(QString::fromStdString(strategy.summary()));
	QString strategyDescription(QString::fromStdString(strategy.description()));
	QString strategyDetails(QString(R".(
<h3>%1</h3>
<br/>
<h3>Sommaire</h3>
<p>%2</p>
<h3>Description</h3>
<p>%3</p>
).").arg(strategyName, strategySummary, strategyDescription));

	QPushButton* descriptionButton{ new QPushButton("Détails") };
	QElidedLabel* title{ new QElidedLabel(QString::fromStdString(strategy.summary())) };

	descriptionButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	connect(descriptionButton, &QPushButton::clicked, [this, strategyName, strategyDetails]() {
			QMessageBox::information(this, strategyName, strategyDetails);
		});

	QHBoxLayout* infoLayout{ new QHBoxLayout };
	infoLayout->addWidget(title);
	infoLayout->addWidget(descriptionButton);

	QFrame* sepFrame{ new QFrame };
	sepFrame->setFrameStyle(static_cast<int>(QFrame::HLine) | static_cast<int>(QFrame::Raised));
	QVBoxLayout* layout{ new QVBoxLayout(this) };
	layout->addLayout(infoLayout);
	layout->addWidget(sepFrame);
	layout->addWidget(dESolutionPanel);
}

de::SolutionStrategy* QDESolutionTabPanel::InternalSolutionPanel::buildSolution() const
{
	return mDESolutionPanel ? mDESolutionPanel->buildSolution() : nullptr;
}

void QDESolutionTabPanel::InternalSolutionPanel::updateVisualization(QDEAdapter const& mDE)
{
	if (mDESolutionPanel) {
		mDESolutionPanel->updateVisualization(mDE);
	}
}
