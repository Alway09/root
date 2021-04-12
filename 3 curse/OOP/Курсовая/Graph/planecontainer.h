#ifndef PLANECONTAINER_H
#define PLANECONTAINER_H

#include <QScrollArea>
#include "coordianteplane.h"
#include <cmath>
#include <QPoint>
#include <QScrollBar>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>

class PlaneContainer : public QScrollArea
{
    Q_OBJECT

public:
    PlaneContainer() = delete;
    PlaneContainer(CoordinatePlane* plane, QWidget* parent = nullptr);
    ~PlaneContainer();



protected:
    void mouseMoveEvent(QMouseEvent* event) override final;
    void mousePressEvent(QMouseEvent* event) override final;
    void wheelEvent(QWheelEvent* event) override final;

public slots:
    void centerize() const;
    void planeSizeChanged();
    void planeHelpLinesFlagChanged(bool flag){ m_plane_helpLinesFlag = flag; }

private:
    CoordinatePlane* m_plane;
    QPoint m_move_point;
    bool m_is_moving;
    bool m_plane_helpLinesFlag;
};

#endif // PLANECONTAINER_H
