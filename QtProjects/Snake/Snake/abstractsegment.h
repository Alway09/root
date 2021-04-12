#ifndef ABSTRACTSEGMENT_H
#define ABSTRACTSEGMENT_H

#include <QGraphicsItem>

enum Orientation{UP, DOWN, LEFT,RIGHT,};
const int default_size(20);

class AbstractSegment : public QGraphicsItem
{
public:
    AbstractSegment(int radius = default_size, Orientation o = UP);
    ~AbstractSegment(){};

    QRectF boundingRect() const override final;
    QPainterPath shape() const override final;

    Orientation getOrient() const{ return m_orient; }
    Orientation& previouseOrient(){ return m_prev_orient; }
    void setOrient(Orientation o){ m_orient = o; }
    int getRadius() const{ return m_radius; }
    bool& justTurned(){ return m_just_turned; }

protected:
    int m_radius;
    Orientation m_orient;
    Orientation m_prev_orient;
    bool m_just_turned;
};

#endif // ABSTRACTSEGMENT_H
