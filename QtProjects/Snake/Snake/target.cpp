#include "target.h"

Target::Target(int radius) : m_radius(radius)
{

}

QRectF Target::boundingRect() const{
    return QRectF(m_radius, m_radius, -m_radius, -m_radius);
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(QBrush(QColor(255, 0, 0)));

    painter->drawEllipse(boundingRect());
}

QPainterPath Target::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
