#include "paintwidget.h"
#include "QPainter"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
}


void PaintWidget::setPixmap(QPixmap *pixmap)
{
    _pixmap = pixmap;
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *_pixmap);
}
