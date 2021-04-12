#include "workarea.h"

WorkArea::WorkArea(QWidget *parent) : QWidget(parent), m_color(128, 128, 128)
{

}

void WorkArea::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit onAreaMousePressed(false);
    }
}

void WorkArea::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), QBrush(m_color));
}

void WorkArea::setColor(QColor color){
    m_color = color;
    repaint();
}

void WorkArea::mouseMoveEvent(QMouseEvent *event){
    const int a(60);
    QPoint temp(mapFromGlobal(event->globalPos()));

    if(temp.x() <= a){
        cursor().setPos(mapToGlobal(QPoint(a + 1, mapFromGlobal(event->globalPos()).y())));
    } else if(temp.y() <= a){
        cursor().setPos(mapToGlobal(QPoint(mapFromGlobal(event->globalPos()).x(), a + 1)));
    } else if(temp.x() >= width() - a){
        cursor().setPos(mapToGlobal(QPoint( width() - a - 1, mapFromGlobal(event->globalPos()).y())));
    } else if(temp.y() >= height() - a){
        cursor().setPos(mapToGlobal(QPoint(mapFromGlobal(event->globalPos()).x(), height() - a - 1)));
    }
}
