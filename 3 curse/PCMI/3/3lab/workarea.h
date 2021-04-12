#ifndef WORKAREA_H
#define WORKAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class WorkArea : public QWidget
{
    Q_OBJECT
public:
    explicit WorkArea(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void setColor(QColor color);
    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void onAreaMousePressed(bool late);

private:
    QColor m_color;

};

#endif // WORKAREA_H
