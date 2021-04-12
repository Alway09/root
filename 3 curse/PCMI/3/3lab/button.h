#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class Button : public QWidget
{
    Q_OBJECT
public:
    explicit Button(int width, int height, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void setSize(int width, int height);
    void setColor(QColor color);

signals:
    void onButtonClicked();

private:
    QColor m_color;
};

#endif // BUTTON_H
