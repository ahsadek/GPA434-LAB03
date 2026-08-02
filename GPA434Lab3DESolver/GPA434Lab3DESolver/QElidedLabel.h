#pragma once



#include <QLabel>


//! \brief _Widget_ utilitaire permettant d'afficher un texte élagué.
//! 
//! \details Ce _widget_ permet d'afficher un texte avec un ellipsis 
//! (trois points de suspension) si le texte est plus grand que la 
//! taille du _widget_.
//! 
//! Ce _widget_ est présent comme outil simplifiant le développement.
class QElidedLabel : public QLabel
{
    Q_OBJECT

public:
    QElidedLabel(QString const& elidedText, QWidget* parent = nullptr);
    QElidedLabel(QWidget* parent = nullptr);

    QString originalText() const;
    void setElidedText(QString const& elidedText);

protected:
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QString mOriginalText;

    void elideText();

};
