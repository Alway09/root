#ifndef COORDINATEPLANE_H
#define COORDINATEPLANE_H

#include <QWidget>
#include <QScrollArea>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPair>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <cmath>

class CoordinatePlane : public QWidget
{
    Q_OBJECT

public:
    explicit CoordinatePlane(QWidget *parent = nullptr);
    ~CoordinatePlane();  

    void zoomIn();
    void zoomOut();
    void setDefaultSize(int size);
    void setData(QJsonDocument* jDoc);

protected:
    void paintEvent(QPaintEvent *event) override final;
    void mousePressEvent(QMouseEvent *event) override final;
    void mouseReleaseEvent(QMouseEvent* event) override final;
    void mouseMoveEvent(QMouseEvent* event) override final;
    void wheelEvent(QWheelEvent* event) override final;

signals:
    void sizeChanged();
    void helpLinesFlagChanged(bool flag);

private:
    int m_current_default_size;   
    int m_current_scale;
    double m_scale_koef1;
    double m_scale_koef2;
    bool m_helpLines_flag;
    bool m_is_cartesian;
    QList<QPair<double, double>>* m_points;
};

#endif // COORDINATEPLANE_H
