#ifndef SCENE_H
#define SCENE_H

#include<QGraphicsScene>
#include<QGraphicsItemGroup>
#include<QGraphicsLineItem>
#include"node.h"

class Scene  : public QGraphicsScene{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);
    Node* getNode(size_t) const;
    size_t getNodeId(size_t) const;
    size_t getNodesAmount() const;
    void addEdge(qreal x1, qreal y1, qreal x2, qreal y2);
    void deleteNodes();
    void deleteEdges();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QVector<QGraphicsLineItem*> edge_v;
    QVector<Node*> node_v;
};

#endif // SCENE_H
