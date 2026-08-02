#include "QImageViewer.h"


#include <QPainter>


QImageViewer::QImageViewer(QImage const& image, QWidget* parent)
    : QImageViewer(QPixmap::fromImage(image), parent)
{
}

QImageViewer::QImageViewer(QPixmap const& image, QWidget* parent)
    : QWidget(parent)
    , mPixmap(image)
    , mNoImageText("No image")
    , mBackgroundColor(QColor(64, 64, 64))
    , mTextColor(QColor(222, 222, 222))
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

QImageViewer::QImageViewer(QWidget* parent)
    : QImageViewer(QPixmap(), parent)
{
}

QImage QImageViewer::image() const
{
    return mPixmap.toImage();
}

QPixmap QImageViewer::pixmap() const
{
    return mPixmap;
}

void QImageViewer::clearImage()
{
    mPixmap = QPixmap();
    update();
}

void QImageViewer::setImage(QImage const& image)
{
    setPixmap(QPixmap::fromImage(image));
}

void QImageViewer::setPixmap(QPixmap const& image)
{
    mPixmap = image;
    update();
}

QColor QImageViewer::backgroundColor() const
{
    return mBackgroundColor;
}

QColor QImageViewer::textColor() const
{
    return mTextColor;
}

QString QImageViewer::noImageText() const
{
    return mNoImageText;
}

void QImageViewer::setBackgroundColor(QColor const& color)
{
    mBackgroundColor = color;
    update();
}

void QImageViewer::setTextColor(QColor const& color)
{
    mTextColor = color;
    update();
}

void QImageViewer::setNoImageText(QString const& text)
{
    mNoImageText = text;
    update();
}

QSize QImageViewer::sizeHint() const
{
    return QSize(200, 200);
}

void QImageViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), mBackgroundColor);
    if (mPixmap.isNull()) {
        drawNoImageText(painter);
    } else {
        QImage resizedImage(mPixmap.toImage().scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QSize s(resizedImage.size());
        QPoint o((size().width() - s.width()) / 2, (size().height() - s.height()) / 2);
        painter.drawImage(QRect(o, s), mPixmap.toImage());
    }
}

void QImageViewer::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    emit resized();
}

void QImageViewer::drawNoImageText(QPainter& painter)
{
    QFont font(painter.font());
    font.setFamily("Courier new");
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(mTextColor);
    painter.drawText(rect(), Qt::AlignCenter, mNoImageText);
}
