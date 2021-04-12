#include "button.h"

Button::Button(int width, int height, QWidget *parent) : QWidget(parent), m_color(128, 0, 0)
{
    setFixedWidth(width);
    setFixedHeight(height);
}

void Button::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(m_color));
    painter.setPen(QPen(QColor(0, 0, 0, 0)));
    painter.drawEllipse(QRect(1, 1, width()-2, height()-2));
    setMask(QRegion(QRect(0, 0, width(), height()), QRegion::Ellipse));
}

void Button::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit onButtonClicked();
    }
}

void Button::setSize(int width, int height){
    setFixedWidth(width);
    setFixedHeight(height);
    updateGeometry();
}

void Button::setColor(QColor color){
    m_color = color;
}
