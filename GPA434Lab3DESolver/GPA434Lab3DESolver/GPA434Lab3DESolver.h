#pragma once

#include <QtWidgets/QMainWindow>

#include "QDEAdapter.h"
#include "ui_GPA434Lab3DESolver.h"

class QDEBestResultPanel;
class QDEControllerPanel;
class QDEEngineParametersPanel;
class QDEHistoryChartPanel;
class QDESolutionTabPanel;


//! \brief Main window assembling the differential evolution application.
class GPA434Lab3DESolver : public QMainWindow
{
    Q_OBJECT

public:
    GPA434Lab3DESolver(QWidget * parent = nullptr);
    GPA434Lab3DESolver(GPA434Lab3DESolver const &) = delete;
    GPA434Lab3DESolver(GPA434Lab3DESolver &&) = delete;
    GPA434Lab3DESolver& operator=(GPA434Lab3DESolver const &) = delete;
    GPA434Lab3DESolver& operator=(GPA434Lab3DESolver &&) = delete;
    ~GPA434Lab3DESolver() override = default;

private:
    QDEAdapter mDEAdapter;
    Ui::GPA434Lab3DESolverClass mUi;

    QDEControllerPanel * mControllerPanel{};
    QDEEngineParametersPanel * mEngineParametersPanel{};
    QDESolutionTabPanel * mSolutionTabPanel{};
    QDEBestResultPanel * mBestResultPanel{};
    QDEHistoryChartPanel * mHistoryChartPanel{};

    void setupGui();
    void assembleInterface();
    void establishConnections();
    void addSolutionPanels();
};
