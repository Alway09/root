#include "head.h"

Head::Head(int radius, Orientation o) : AbstractSegment(radius, o)
{

}

void Head::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(QBrush(QColor(0, 255, 0)));
    painter->setPen(QPen(QColor(255, 0, 0), m_radius/10));

    painter->drawEllipse(boundingRect());
    switch (m_orient) {
    case UP:
        painter->drawPoint(m_radius*0.3, m_radius*0.4);
        painter->drawPoint(m_radius*0.7, m_radius*0.4);
        break;
    case DOWN:
        painter->drawPoint(m_radius*0.3, m_radius*0.6);
        painter->drawPoint(m_radius*0.7, m_radius*0.6);
        break;
    case LEFT:
        painter->drawPoint(m_radius*0.4, m_radius*0.3);
        painter->drawPoint(m_radius*0.4, m_radius*0.7);
        break;
    case RIGHT:
        painter->drawPoint(m_radius*0.6, m_radius*0.3);
        painter->drawPoint(m_radius*0.6, m_radius*0.7);
        break;
    }
}
