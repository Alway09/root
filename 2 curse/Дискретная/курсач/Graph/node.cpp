#include "node.h"
#include"scene.h"

#include<QGraphicsEllipseItem>
#include<QGraphicsSimpleTextItem>
#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QPen>
#include<QBrush>

int jump_size{1};

Node::Node() : QGraphicsEllipseItem(-12,-12,12*2,12*2), radius(12)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    QBrush brush1(Qt::SolidPattern);
    brush1.setColor(Qt::GlobalColor::white);
    setBrush(brush1);
    self_id = id;
    QGraphicsSimpleTextItem* num = new QGraphicsSimpleTextItem(QString::number(id), this);
    if(id < 10){
        num->setPos(-3,-7);
    } else if(id < 100){
        num->setPos(-7,-7);
    }

    id++;
}

size_t Node::id{1};

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(collidingItems().size() <= 1){
        this->setPos(mapToScene(event->pos()));
    } else{
        for(int i = 0; i < collidingItems().size(); i++){
            if(collidingItems().toVector()[i]->type() == UserType + 1) {
                if(collidingItems().toVector()[i]->pos().x() >= pos().x() && collidingItems().toVector()[i]->pos().y() >= pos().y()){
                    collidingItems().toVector()[i]->moveBy(jump_size,jump_size);
                } else if(collidingItems().toVector()[i]->pos().x() >= pos().x() && collidingItems().toVector()[i]->pos().y() <= pos().y()){
                    collidingItems().toVector()[i]->moveBy(jump_size,-jump_size);
                } else if(collidingItems().toVector()[i]->pos().x() <= pos().x() && collidingItems().toVector()[i]->pos().y() <= pos().y()){
                    collidingItems().toVector()[i]->moveBy(-jump_size,-jump_size);
                } else if(collidingItems().toVector()[i]->pos().x() <= pos().x() && collidingItems().toVector()[i]->pos().y() >= pos().y()){
                    collidingItems().toVector()[i]->moveBy(-jump_size,jump_size);
                }
            }
        }
    }
}

size_t Node::getSelfId() const{
    return self_id;
}
