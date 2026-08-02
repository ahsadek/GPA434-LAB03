#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GPA434Lab3DESolver.h"


class GPA434Lab3DESolver : public QMainWindow
{
    Q_OBJECT

public:
    GPA434Lab3DESolver(QWidget *parent = nullptr);
    ~GPA434Lab3DESolver() override;

private:
    Ui::GPA434Lab3DESolverClass ui;
};
