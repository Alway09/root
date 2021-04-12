#include "scene.h"
#include<QGraphicsSceneMouseEvent>
#include<QRectF>
#include"node.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mousePressEvent(event);
    QPointF position = event->scenePos();
    if(event->button() == Qt::RightButton){
        Node* gr = new Node();
        gr->setPos(position);
        for(Node* elem : node_v){
            if(gr->collidesWithItem(elem)){
                delete(gr);
                //delete(elem);
                Node::id--;
                for(int i = 0; i < node_v.size(); i++){
                    if(node_v[i] == elem){
                        node_v.remove(i);
                        delete(elem);
                        break;
                    }
                }
                return;
            }
        }
        addItem(gr);
        node_v.push_back(gr);
    }
}

Node* Scene::getNode(size_t i) const {
    return node_v[i];
}

size_t Scene::getNodeId(size_t i) const{
    return node_v[i]->getSelfId();
}

size_t Scene::getNodesAmount() const{
    return node_v.size();
}

void Scene::addEdge(qreal x1, qreal y1, qreal x2, qreal y2){
    QGraphicsLineItem* edge = new QGraphicsLineItem(x1, y1, x2, y2);
    edge->setZValue(-1);
    addItem(edge);
    edge_v.push_back(edge);
}

void Scene::deleteNodes(){
    for(int i = 0; i < node_v.size(); i++){
        delete(node_v[i]);
    }
    node_v.clear();
}

void Scene::deleteEdges(){
    for(int i = 0; i < edge_v.size(); i++){
        delete(edge_v[i]);
    }
    edge_v.clear();
}
