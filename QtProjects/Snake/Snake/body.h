#ifndef BODY_H
#define BODY_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include "abstractsegment.h"

class Body : public AbstractSegment
{
public:
    Body(Orientation o = UP, int radius = default_size);
    Body(Body& other);

    ~Body(){};

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    //int& turnings(){return m_turnings;}
    QVector<int>& needToWalk(){return m_need_to_walk;}
    bool& stepToTurn(){ return m_step_to_turn; }

    static int amount;


private:
    //int m_turnings;
    QVector<int> m_need_to_walk;
    bool m_step_to_turn;
};

#endif // BODY_H
