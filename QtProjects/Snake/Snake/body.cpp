#include "body.h"

Body::Body(Orientation o, int radius) : AbstractSegment(radius, o), m_need_to_walk(0),  m_step_to_turn(false)
{
    ++amount;
}

Body::Body(Body& other): AbstractSegment(other.getRadius(), other.getOrient()),
    m_need_to_walk(other.needToWalk())
{
    ++amount;
}

int Body::amount(0);

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(QBrush(QColor(0, 255, 0)));
    painter->setPen(QPen(QColor(255, 0, 0), m_radius/10));

    painter->drawEllipse(boundingRect());
}
