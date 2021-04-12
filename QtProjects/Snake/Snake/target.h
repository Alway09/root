#ifndef TARGET_H
#define TARGET_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>

class Target : public QGraphicsItem
{
public:
    Target(int radius = 15);
    ~Target(){};

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPainterPath shape() const override;

    int getRadius() const{ return m_radius; }
    void setRadius(int r){ m_radius = r; }

private:
    int m_radius;
};

#endif // TARGET_H
