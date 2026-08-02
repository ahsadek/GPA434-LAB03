#pragma once



#include <QGroupBox>

class QPlainTextEdit;
class QDEAdapter;


//! \brief Panneau affichant les résultats textuels lors de l'évolution.
class QDEBestResultPanel : public QGroupBox
{
	Q_OBJECT

public:
	QDEBestResultPanel(QDEAdapter const& de, QWidget * parent = nullptr);
	QDEBestResultPanel(QDEBestResultPanel const &) = default;
	QDEBestResultPanel(QDEBestResultPanel &&) = default;
	QDEBestResultPanel& operator=(QDEBestResultPanel const &) = default;
	QDEBestResultPanel& operator=(QDEBestResultPanel &&) = default;
	~QDEBestResultPanel() override = default;

public slots:
	void updateBestResult();
	void reset();

private:
	QDEAdapter const& mDEAdapter;
	QPlainTextEdit* mPlainTextEdit;

	void setupGUI();
	void assemblingAndLayouting();
	void establishConnections();
};
