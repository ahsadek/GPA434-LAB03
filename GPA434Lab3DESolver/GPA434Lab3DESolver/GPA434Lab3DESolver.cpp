#include "GPA434Lab3DESolver.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QSizePolicy>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

#include "QDEBestResultPanel.h"
#include "QDEControllerPanel.h"
#include "QDEEngineParametersPanel.h"
#include "QDEHistoryChartPanel.h"
#include "QDEGeometricPanel.h"
#include "QDEOpenBoxPanel.h"
#include "QDEPeakPanel.h"
#include "QDESmileyPanel.h"
#include "QDESolutionTabPanel.h"


GPA434Lab3DESolver::GPA434Lab3DESolver(QWidget * parent)
    : QMainWindow(parent)
    , mDEAdapter{}
    , mControllerPanel{ new QDEControllerPanel(mDEAdapter) }
    , mEngineParametersPanel{ new QDEEngineParametersPanel(mDEAdapter) }
    , mSolutionTabPanel{ new QDESolutionTabPanel(mDEAdapter) }
    , mBestResultPanel{ new QDEBestResultPanel(mDEAdapter) }
    , mHistoryChartPanel{ new QDEHistoryChartPanel(mDEAdapter) }
{
    mUi.setupUi(this);

    setupGui();
    assembleInterface();
    establishConnections();
    addSolutionPanels();
}

void GPA434Lab3DESolver::setupGui()
{
    setWindowTitle("Differential Evolution Solver");
    setWindowIcon(QIcon(":/GPA434Lab3DESolver/dna-icon"));
    resize(1200, 800);
}

void GPA434Lab3DESolver::assembleInterface()
{
    QWidget * controlWidget{ new QWidget };
    controlWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QVBoxLayout * controlLayout{ new QVBoxLayout(controlWidget) };
    controlLayout->addWidget(mControllerPanel);
    controlLayout->addWidget(mEngineParametersPanel);
    controlLayout->addWidget(mBestResultPanel);

    QSplitter * visualizationSplitter{ new QSplitter(Qt::Vertical) };
    visualizationSplitter->addWidget(mSolutionTabPanel);
    visualizationSplitter->addWidget(mHistoryChartPanel);
    visualizationSplitter->setStretchFactor(0, 3);
    visualizationSplitter->setStretchFactor(1, 1);

    QHBoxLayout * contentLayout{ new QHBoxLayout };
    contentLayout->addWidget(controlWidget);
    contentLayout->addWidget(visualizationSplitter);

    QVBoxLayout * mainLayout{ new QVBoxLayout(mUi.centralWidget) };
    mainLayout->addLayout(contentLayout);
}

void GPA434Lab3DESolver::establishConnections()
{
    connect(mEngineParametersPanel, &QDEEngineParametersPanel::parameterChanged,
            mControllerPanel, &QDEControllerPanel::resetSimulation);
    connect(mEngineParametersPanel, &QDEEngineParametersPanel::parameterChanged,
            mSolutionTabPanel, &QDESolutionTabPanel::updateVisualization);

    connect(mSolutionTabPanel, &QDESolutionTabPanel::solutionChanged,
            mEngineParametersPanel, &QDEEngineParametersPanel::setParametersFromSolution);
    connect(mSolutionTabPanel, &QDESolutionTabPanel::solutionChanged,
            mControllerPanel, &QDEControllerPanel::resetSimulation);

    connect(mControllerPanel, &QDEControllerPanel::evolutionStarted,
            mEngineParametersPanel, &QDEEngineParametersPanel::disable);
    connect(mControllerPanel, &QDEControllerPanel::evolutionStopped,
            mEngineParametersPanel, &QDEEngineParametersPanel::enable);
    connect(mControllerPanel, &QDEControllerPanel::evolutionStarted,
            mSolutionTabPanel, &QDESolutionTabPanel::disable);
    connect(mControllerPanel, &QDEControllerPanel::evolutionStopped,
            mSolutionTabPanel, &QDESolutionTabPanel::enable);
}

void GPA434Lab3DESolver::addSolutionPanels()
{
    // Panneau retiré volontairement: depuis la mise à jour de Qt, ce panneau génère
    // un avertissement de compilation. Nous préférons une compilation sans warning.

    //mSolutionTabPanel->addSolutionPanel(new QDEPeakPanel);

    mSolutionTabPanel->addSolutionPanel(new QDEOpenBoxPanel);
    mSolutionTabPanel->addSolutionPanel(new QDEGeometricPanel);
    mSolutionTabPanel->addSolutionPanel(new QDESmileyPanel);
}
