#include "button1.h"

Button1::Button1(int width, int height, QWidget *parent) : QWidget(parent), m_color(128, 0, 0)
{
    setFixedWidth(width);
    setFixedHeight(height);
}

void Button1::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(QRect(0, 0, width(), height()), QBrush(m_color));
}

void Button1::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit onButtonClicked();
    }
}

void Button1::setSize(int width, int height){
    setFixedWidth(width);
    setFixedHeight(height);
    repaint();
}

void Button1::setColor(QColor color){
    m_color = color;
}
