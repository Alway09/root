#ifndef BUTTON1_H
#define BUTTON1_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class Button1 : public QWidget
{
    Q_OBJECT
public:
    explicit Button1(int width, int height, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void setSize(int width, int height);
    void setColor(QColor color);

signals:
    void onButtonClicked();

private:
    QColor m_color;
};

#endif // BUTTON1_H
