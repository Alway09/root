#ifndef HEAD_H
#define HEAD_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QKeyEvent>
#include "abstractsegment.h"

class Head : public AbstractSegment
{
    //Q_OBJECT

public:
    explicit Head(int radius = default_size, Orientation o = UP);
    ~Head(){};

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // HEAD_H
