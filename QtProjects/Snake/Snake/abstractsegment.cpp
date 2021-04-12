#include "abstractsegment.h"

AbstractSegment::AbstractSegment(int radius, Orientation o) : QGraphicsItem(), m_radius(radius), m_orient(o), m_prev_orient(o), m_just_turned(false)
{

}

QRectF AbstractSegment::boundingRect() const{
    return QRectF(m_radius, m_radius, -m_radius, -m_radius);
}

QPainterPath AbstractSegment::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
