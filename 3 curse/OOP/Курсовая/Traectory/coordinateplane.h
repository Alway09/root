#ifndef COORDINATEPLANE_H
#define COORDINATEPLANE_H

#include <QWidget>
#include <QScrollArea>
#include <QPair>
#include <QPainter>


class CoordinatePlane : public QWidget
{
    Q_OBJECT

private:
    class LocalScrollArea : public QScrollArea
    {
    public:
        explicit LocalScrollArea(QWidget* parent = nullptr);
        void wheelEvent(QWheelEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void resizeEvent(QResizeEvent *) override;
        CoordinatePlane* getPlane() const {return static_cast<CoordinatePlane*>(widget());}
    };

public:
    explicit CoordinatePlane(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    LocalScrollArea* getScrollArea() const { return m_scrollArea;};
    void setData(QVector<QPair<double, double>> data);

private:
    friend class LocalScrollArea;

    void zoomIn();
    void zoomOut();

    int m_current_scale;    //double
    double m_scale_coefficient;
    LocalScrollArea* m_scrollArea;
    QVector<QPair<double, double>> m_points;

public slots:
    void resetZoom();

};

#endif // COORDINATEPLANE_H
