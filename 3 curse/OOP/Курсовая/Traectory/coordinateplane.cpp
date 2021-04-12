#include "coordinateplane.h"
#include<QPalette>
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QWheelEvent>
#include<QScrollBar>
#include<QScrollArea>
#include<QPainterPath>
#include<QPushButton>
#include<iostream>
#include<QFont>
#include<QVector>
#include<QStack>
#include<math.h>

#define TRIANGLE_SIZE 5
#define MAX_SCALE 500

//-------------------------------------------------------------
using Points = QVector<QPair<double, double> >;
//-------------------------------------------------------------
void drawTriangles(QPainter&, size_t, size_t, size_t, size_t);
double findMax(const Points&);
//-------------------------------------------------------------
static float g_zoom_size(1);
static QStack<int> g_zoom_scale_points;
static QPair<int,int> g_default_size(0,0);
static QPair<int, int> g_prev_size(0,0);    // для масштабирования колесом мыши
static QPair<int, int> g_move_point(0,0);   // для навигации с помощью мыши
static bool g_helpLines_on(false);          // для включения/отключения отрисовки вспомогательных линий
static double k1(80), k2(1);               // коэффициенты для масштабирования
//-------------------------------------------------------------

CoordinatePlane::LocalScrollArea::LocalScrollArea(QWidget* parent) : QScrollArea(parent){};

CoordinatePlane::CoordinatePlane(QWidget *parent) : QWidget(nullptr), m_current_scale(1),m_scale_coefficient(360), m_scrollArea(new LocalScrollArea(parent)), m_points(Points())
{
    m_scrollArea->setFixedSize(parent->width(), parent->height());
    //m_scrollArea->horizontalScrollBar()->hide();
    //m_scrollArea->verticalScrollBar()->hide();

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    g_default_size.first = m_scrollArea->width();
    g_default_size.second = m_scrollArea->height();

    /*g_edge_points.first.rx() = g_default_size.first;
    g_edge_points.first.rx() = g_default_size.second/2;
    g_edge_points.second.rx() = g_default_size.first/2;
    g_edge_points.second.ry() = g_default_size.second;*/

    resize(g_default_size.first, g_default_size.second);

    m_scrollArea->setWidget(this);

    QPushButton* zoomOut = new QPushButton("");
    connect(zoomOut, SIGNAL(clicked()), this, SLOT(resetZoom()));
    m_scrollArea->setCornerWidget(zoomOut);
}

void CoordinatePlane::LocalScrollArea::resizeEvent(QResizeEvent *event){
    /*QPoint point = widget()->mapFrom(this, QPoint(width(), height()));
    if(point.x() > widget()->width() || point.y() > widget()->height()){
        if(!horizontalScrollBar()->value()){
            g_default_size.first = widget()->width() + (event->size().width() - event->oldSize().width());
            widget()->resize(g_default_size.first, g_default_size.second);
        }
        if(!verticalScrollBar()->value()){
            g_default_size.second = widget()->height() + (event->size().height() - event->oldSize().height());
            widget()->resize(g_default_size.first, g_default_size.second);
        }
        getPlane()->m_current_scale = 1;
    }*/
}

void CoordinatePlane::resetZoom(){
    m_current_scale = 1;
    resize(g_default_size.first, g_default_size.second);
    update();
}

void CoordinatePlane::zoomIn(){
    if(m_current_scale < MAX_SCALE){
        if(g_zoom_size < 32 && !(m_current_scale % 20)){
            g_zoom_scale_points.push(m_current_scale);
            g_zoom_size *= 2;
        }
        m_current_scale += g_zoom_size;
        resize(g_default_size.first*m_current_scale, g_default_size.second*m_current_scale);
    }
}

void CoordinatePlane::zoomOut(){
    if(m_current_scale > 1){
        if(g_zoom_size > 1 && m_current_scale == g_zoom_scale_points.top()){
            g_zoom_size /= 2;
            g_zoom_scale_points.pop();
        }
        m_current_scale -= g_zoom_size;
        resize(g_default_size.first*m_current_scale, g_default_size.second*m_current_scale);
    };
}
//-------------------------------------------------------------
void CoordinatePlane::LocalScrollArea::wheelEvent(QWheelEvent*){
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + (widget()->width() - g_prev_size.first)/2);
    verticalScrollBar()->setValue(verticalScrollBar()->value() + (widget()->height() - g_prev_size.second)/2);
}

void CoordinatePlane::wheelEvent(QWheelEvent *event){
    g_prev_size.first = width();
    g_prev_size.second = height();
    if(event->delta() > 0){
        zoomIn();
    } else{
        zoomOut();
    }
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void CoordinatePlane::LocalScrollArea::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        g_helpLines_on = true;
        getPlane()->update();
    } else{
        g_move_point.first = horizontalScrollBar()->value() + event->x();
        g_move_point.second = verticalScrollBar()->value() + event->y();
    }
}

void CoordinatePlane::LocalScrollArea::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        g_helpLines_on = false;
    }
    getPlane()->update();
}

void CoordinatePlane::LocalScrollArea::mouseMoveEvent(QMouseEvent *event){
    if(!g_helpLines_on){
        horizontalScrollBar()->setValue(g_move_point.first - event->x());
        verticalScrollBar()->setValue(g_move_point.second - event->y());
    }
    getPlane()->update();
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void CoordinatePlane::setData(Points data){
    m_points = data;
    if(!m_points.isEmpty()){
        double max = findMax(m_points);
        //-------------------------------------------------------------     подгонка масштаба под график
        while(width()/2 + m_current_scale/k2 * max < width() && height()/2 + m_current_scale/k2 * max < height()){
            k2 -= 0.001;
        }
        while(width()/2 + m_current_scale/k2 * max > width() && height()/2 + m_current_scale/k2 * max > height()){
            k2 += 0.0001;
        }
        //-------------------------------------------------------------
        k1 = max*0.5;
    }
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void CoordinatePlane::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::RenderHint::TextAntialiasing);
    painter.setPen(QPen(QBrush(Qt::black), 2));

    //-------------------------------------------------------------     оси X и Y
    painter.drawLine(0, height()/2, width(), height()/2);
    painter.drawLine(width()/2, 0, width()/2, height());
    //-------------------------------------------------------------     стрелки
    size_t hor_value = m_scrollArea->horizontalScrollBar()->value() + m_scrollArea->horizontalScrollBar()->pageStep();
    size_t ver_value =m_scrollArea->verticalScrollBar()->value() + m_scrollArea->verticalScrollBar()->pageStep();
    drawTriangles(painter, width(), height(), hor_value, ver_value);
    //-------------------------------------------------------------     сетка
    painter.save();

    QPen pen_lines(QBrush(QColor(0,0,0,40)), 1);
    QPen pen_numbers(QBrush(QColor(0,0,255)), 1);

    int font_size(16);
    float font_aligment(0);
    QFont font_numbers = painter.font();
    font_numbers.setPixelSize(font_size);
    painter.setFont(font_numbers);

    if(k1*m_current_scale/k2 > (m_scrollArea->width()*0.2)){
        k1 /= 2;
    } else if(k1*m_current_scale/k2 < (m_scrollArea->width()*0.1)){
        k1 *= 2;
    }
    double size_of_cell(k1*m_current_scale/k2);

    double center(width()/2);
    int num_on_cell(0);
    painter.setPen(pen_numbers);
    QString num(QString::number(num_on_cell));
    painter.drawText(center + 4, height()/2 - 4, num);
    painter.setPen(pen_lines);
    ++num_on_cell;

    while((center += size_of_cell) < width()){        // drawing vertical lines
        painter.drawLine(center, 0, center, height());
        painter.setPen(pen_numbers);
        num = QString::number(num_on_cell * k1);
        font_aligment = font_size/4 * num.size();
        painter.drawText(center - font_aligment, height()/2 - 4, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    center = width()/2;
    num_on_cell = 1;
    while((center -= size_of_cell) >= 0){
        painter.drawLine(center, 0, center, height());
        painter.setPen(pen_numbers);
        num = QString::number(-num_on_cell * k1);
        font_aligment = font_size/4 * num.size();
        painter.drawText(center - font_aligment, height()/2 - 4, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }

    center = height()/2;
    num_on_cell = 1;
    while((center += size_of_cell) < height()){        // drawing horizontal lines
        painter.drawLine(0, center, width(), center);
        painter.setPen(pen_numbers);
        num = QString::number(num_on_cell * k1);
        font_aligment = font_size/1.4 * num.size();
        painter.drawText(width()/2 - font_aligment, center, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    center = height()/2;
    num_on_cell = 1;
    while((center -= size_of_cell) >= 0){
        painter.drawLine(0, center, width(), center);
        painter.setPen(pen_numbers);
        num = QString::number(-num_on_cell * k1);
        font_aligment = font_size/1.4 * num.size();
        painter.drawText(width()/2 - font_aligment, center, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }

    painter.restore();
    //-------------------------------------------------------------     график
    if(!m_points.isEmpty()){
        painter.save();
        painter.setPen(QPen(QBrush(QColor(255,0,0,255)), 3));
        Points::const_iterator iter = m_points.constBegin();
        painter.drawPoint(width()/2 + m_current_scale/k2 * iter->first, height()/2 + m_current_scale/k2 * iter->second);
        while(iter != m_points.constEnd()) {
            ++iter;
            painter.drawPoint(width()/2 + m_current_scale/k2 * iter->first, height()/2 + m_current_scale/k2 * iter->second);
            painter.drawLine(width()/2 + m_current_scale/k2 * iter->first, height()/2 + m_current_scale/k2 * iter->second, \
                             width()/2 + m_current_scale/k2 * (iter-1)->first, height()/2 + m_current_scale/k2 * (iter-1)->second);
        }
        painter.restore();
    }
    //-------------------------------------------------------------     вспомогательные линии
    if(g_helpLines_on){
        painter.save();
        QFont font = painter.font();
        short f_size(13);
        font.setPixelSize(f_size);
        painter.setFont(font);
        painter.setPen(QPen(QBrush(QColor(0,128,128)), 2));

        QPoint coordinates = mapFromGlobal(QCursor::pos());
        painter.drawLine(coordinates.x(), 0, coordinates.x(), height());
        painter.drawLine(0, coordinates.y(), width(), coordinates.y());
        painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + f_size + 2, "x: " + QString::number((coordinates.x() - width()/2) / (m_current_scale/k2)));
        painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + 2*f_size + 2, "y: " + QString::number((coordinates.y() - height()/2) / (m_current_scale/k2)));

        painter.restore();
    }
    //-------------------------------------------------------------     показатель масштаба
    //if(m_current_scale > 1){
        painter.save();
        QFont font = painter.font();
        short f_size(30);
        font.setPixelSize(f_size);
        painter.setFont(font);
        painter.setPen(QPen(QBrush(QColor(128,128,128,255)), 2));

        QString str("X" + QString::number(floor(m_current_scale*100)/100));
        painter.drawText(mapFrom(m_scrollArea, QPoint(m_scrollArea->width() - 3*f_size - 10, m_scrollArea->height() - f_size + 8)), str);
        painter.restore();
    //}
    //-------------------------------------------------------------
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void drawTriangles(QPainter& painter, size_t width, size_t height, size_t hor_value, size_t ver_value){
    QPainterPath triangle;

    triangle.moveTo(hor_value, height/2);
    triangle.lineTo(hor_value - TRIANGLE_SIZE - 12, (height/2) - TRIANGLE_SIZE);
    triangle.lineTo(hor_value - TRIANGLE_SIZE - 12, (height/2) + TRIANGLE_SIZE);
    triangle.lineTo(hor_value, height/2);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.fillPath(triangle, QBrush(Qt::black));
    painter.restore();
    triangle.clear();

    triangle.moveTo(width/2, ver_value);
    triangle.lineTo((width/2) - TRIANGLE_SIZE, ver_value - TRIANGLE_SIZE - 12);
    triangle.lineTo((width/2) + TRIANGLE_SIZE, ver_value - TRIANGLE_SIZE - 12);
    triangle.lineTo(width/2, ver_value);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.fillPath(triangle, QBrush(Qt::black));
    painter.restore();
}
//-------------------------------------------------------------
//-------------------------------------------------------------
double findMax(const Points& vector){
    int max_x(abs(vector[0].first));
    int max_y(abs(vector[0].second));
    Points::const_iterator iter;
    for(iter = vector.constBegin()+1; iter != vector.constEnd(); ++iter){
        if(abs(iter->first) > max_x) max_x = abs(iter->first);
        if(abs(iter->second) > max_y) max_y = abs(iter->second);
    }
    return (max_x > max_y) ? max_x : max_y;
}
//-------------------------------------------------------------
