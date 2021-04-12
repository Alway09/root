#ifndef NODE_H
#define NODE_H

#include<QGraphicsEllipseItem>

class Node : public QGraphicsEllipseItem
{
public:
    Node();
    size_t getSelfId() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    enum {Type = UserType + 1};
    int type() const override {return Type;};
    static size_t id;

private:
    size_t self_id;
    int radius;
};

#endif // NODE_H
