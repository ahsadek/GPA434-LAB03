#pragma once
#ifndef Q_IMAGE_VIEWER_H
#define Q_IMAGE_VIEWER_H


#include <QWidget>


//! \brief _Widget_ utilitaire permettant d'afficher simplement une 
//! image.
//! 
//! \details Ce _widget_ permet d'afficher une image sans contrainte sur la 
//! taille du _widget_ (comme `QLabel` le fait). La proportionnalité de 
//! l'image est respectéem, sans rognage et toujours centrée.
//! 
//! Une couleur de fond est également disponible pour les cas où l'image ne 
//! rempli pas la surface du _widget_.
//! 
//! Lorqu'il n'y a pas d'image, un texte peut être affiché à la place.
//! 
//! Ce _widget_ est présent comme outil simplifiant le développement.
class QImageViewer : public QWidget
{
    Q_OBJECT

public:
    QImageViewer(QImage const& image, QWidget * parent = nullptr);
    QImageViewer(QPixmap const& image, QWidget * parent = nullptr);
    QImageViewer(QWidget * parent = nullptr);
    QImageViewer(QImageViewer const &) = default;
    QImageViewer(QImageViewer &&) = default;
    QImageViewer& operator=(QImageViewer const &) = default;
    QImageViewer& operator=(QImageViewer &&) = default;
    ~QImageViewer() override = default;

    QImage image() const;
    QPixmap pixmap() const;

    void clearImage();
    void setImage(QImage const & image);
    void setPixmap(QPixmap const & image);

    QColor backgroundColor() const;
    QColor textColor() const;
    QString noImageText() const;

    void setBackgroundColor(QColor const & color);
    void setTextColor(QColor const & color);
    void setNoImageText(QString const & text);

signals:
    void resized();

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QPixmap mPixmap;
    QString mNoImageText;
    QColor mBackgroundColor;
    QColor mTextColor;

    void drawNoImageText(QPainter & painter);
};


#endif // Q_IMAGE_VIEWER_H