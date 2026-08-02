#include "QElidedLabel.h"


QElidedLabel::QElidedLabel(QString const& elidedText, QWidget* parent)
    : QLabel(parent)
    , mOriginalText(elidedText)
{
    elideText();
    //setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
}

QElidedLabel::QElidedLabel(QWidget* parent)
    : QElidedLabel("", parent)
{
}

QString QElidedLabel::originalText() const
{
    return mOriginalText;
}

void QElidedLabel::setElidedText(QString const& text)
{
    mOriginalText = text;
    elideText();
}

QSize QElidedLabel::sizeHint() const
{
    QSize sizeHint(QLabel::sizeHint());
    sizeHint.setWidth(QWIDGETSIZE_MAX);
    return sizeHint;
}

void QElidedLabel::resizeEvent([[maybe_unused]] QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    elideText();
}

void QElidedLabel::elideText()
{
    QLabel::setText(QFontMetrics(font()).elidedText(mOriginalText, Qt::ElideRight, width()));
}

