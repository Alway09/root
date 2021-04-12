#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>
#include <QKeyEvent>
#include <QThread>
#include <QRandomGenerator>
#include <QLabel>
#include <QPair>
#include <iostream>
#include <cmath>
#include "head.h"
#include "body.h"
#include "target.h"
#include "abstractsegment.h"

class Playground : public QGraphicsView
{
   // Q_OBJECT

public:
    Playground(uint w, uint h, QWidget* parent);
    ~Playground();

    void addToSnake(AbstractSegment* elem, int posx, int posy);
    void placeTarget() const;
    void setup();
    void moving();
    void stop();
    void respawn();
    int& segmentsInSnake(){ return m_segments_in_snake; }

    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent* timer) override;

private:
    QList<AbstractSegment*> m_snake;
    Head *m_head;
    Target *m_target;
    QLabel* m_points;
    QPair<QLabel*, QLabel*> m_pause_labels;
    QPair<QLabel*, QLabel*> m_game_over_labels;
    int m_width;
    int m_heigh;
    int m_segments_in_snake;
    QWidget* m_parent;
};

#endif // PLAYGROUND_H
