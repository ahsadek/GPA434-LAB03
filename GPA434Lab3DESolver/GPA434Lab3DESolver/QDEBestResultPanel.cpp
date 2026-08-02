#include "QDEBestResultPanel.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include "QDEAdapter.h"


QDEBestResultPanel::QDEBestResultPanel(QDEAdapter const& de, QWidget *parent)
	: QGroupBox("Solutions obtenues", parent)
	, mDEAdapter{ de }
	, mPlainTextEdit{ new QPlainTextEdit }
{
	setupGUI();
	assemblingAndLayouting();
	establishConnections();
}

void QDEBestResultPanel::updateBestResult()
{
	mPlainTextEdit->setPlainText(mDEAdapter.bestSolutionInfo());
}

void QDEBestResultPanel::reset()
{
	mPlainTextEdit->setPlainText("- no result -");
}

void QDEBestResultPanel::setupGUI()
{
	mPlainTextEdit->setReadOnly(true);

	QFont font{ mPlainTextEdit->document()->defaultFont() };
	font.setFamily("Courier New");
	mPlainTextEdit->document()->setDefaultFont(font);

	reset();
}

void QDEBestResultPanel::assemblingAndLayouting()
{
	QVBoxLayout* layout{ new QVBoxLayout(this) };
	layout->addWidget(mPlainTextEdit);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
}

void QDEBestResultPanel::establishConnections()
{
	connect(&mDEAdapter, &QDEAdapter::oneEvolutionStepped, this, &QDEBestResultPanel::updateBestResult);
	connect(&mDEAdapter, &QDEAdapter::wasReset, this, &QDEBestResultPanel::reset);
}
