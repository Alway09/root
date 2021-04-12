#include "coordianteplane.h"

#define MAX_SCALE 500
using Points = QList<QPair<double, double>>*;

CoordinatePlane::CoordinatePlane(QWidget *parent) : QWidget(parent), m_current_scale(1), m_scale_koef1(80), m_scale_koef2(1), m_helpLines_flag(false), m_is_cartesian(false), m_points(new QList<QPair<double, double>>)
{
    //resize(m_current_default_size, m_current_default_size);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

CoordinatePlane::~CoordinatePlane()
{
    delete m_points;
}

void CoordinatePlane::setDefaultSize(int size){
    m_current_default_size = size;
    resize(m_current_default_size, m_current_default_size);
}

void CoordinatePlane::zoomIn(){
    if(m_current_scale < MAX_SCALE){
        m_current_scale += 1;
        resize(m_current_default_size*m_current_scale, m_current_default_size*m_current_scale);
    }
}

void CoordinatePlane::zoomOut(){
    if(m_current_scale > 1){
        m_current_scale -= 1;
        resize(m_current_default_size*m_current_scale, m_current_default_size*m_current_scale);
    }
}

void CoordinatePlane::wheelEvent(QWheelEvent *event){
    //int prevSize(width());

    if(event->angleDelta().y() > 0){
        zoomIn();
    } else{
        zoomOut();
    }

    emit sizeChanged();
}

void CoordinatePlane::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::MouseButton::RightButton){
        m_helpLines_flag = true;
        emit helpLinesFlagChanged(m_helpLines_flag);
        repaint();
    }
    event->ignore();
}

void CoordinatePlane::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::MouseButton::RightButton){
        m_helpLines_flag = false;
        emit helpLinesFlagChanged(m_helpLines_flag);
        repaint();
    }
    event->ignore();
}

void CoordinatePlane::mouseMoveEvent(QMouseEvent *event){
    if(m_helpLines_flag){
        repaint();
    }
    event->ignore();
}

double findMax(const QList<QPair<double, double>> list){
    double max_x(abs(list[0].first));
    double max_y(abs(list[0].second));
    QList<QPair<double, double>>::const_iterator iter;
    for(iter = list.constBegin()+1; iter != list.constEnd(); ++iter){
        if(abs(iter->first) > max_x) max_x = abs(iter->first);
        if(abs(iter->second) > max_y) max_y = abs(iter->second);
    }
    return (max_x > max_y) ? max_x : max_y;
}

void CoordinatePlane::setData(QJsonDocument *jDoc){
    if(!m_points->isEmpty()){
        delete m_points;
        m_points = new QList<QPair<double, double>>;
    }

    QJsonArray* arr = new QJsonArray(jDoc->array());

    if((*arr)[0].toObject()["system"] == "C"){
        m_is_cartesian = true;
    }else if((*arr)[0].toObject()["system"] == "P"){
        m_is_cartesian = false;
    }

    QJsonArray::iterator arrIter(arr->begin() + 1);
    while(arrIter < arr->end()){
        m_points->append(QPair<double, double>(arrIter->toObject()["x"].toDouble(), -1 * arrIter->toObject()["y"].toDouble()));
        ++arrIter;
    }
    //if(jDoc){a
    delete arr;
    delete jDoc;
    //}

    if(!m_points->isEmpty()){
        double max = findMax(*m_points);
        if(max < 1){
            m_scale_koef2 = 0.05;
        }
        //-------------------------------------------------------------     подгонка масштаба под график
        while(width()/2 + m_current_scale/m_scale_koef2 * max < width()){
            if(max < 1){
                m_scale_koef2 -= 0.00001;
            } else{
                m_scale_koef2 -= 0.001;
            }
            if(m_scale_koef2 <= 0){
                break;
            }
        }
        while(width()/2 + m_current_scale/m_scale_koef2 * max > width()){
            m_scale_koef2 += 0.0001;
        }
        m_scale_koef2 *= 1.5;
        //-------------------------------------------------------------
        m_scale_koef1 = max*0.4;
    }

    repaint(rect());
}

void CoordinatePlane::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::RenderHint::TextAntialiasing);
    painter.setPen(QPen(QBrush(Qt::black), 2));
    //-------------------------------------------------------------     оси X и Y
    painter.drawLine(0, height()/2, width(), height()/2);
    painter.drawLine(width()/2, 0, width()/2, height());
    //-------------------------------------------------------------     сетка
    painter.save();

    QPen pen_lines(QBrush(QColor(0,0,0,40)), 1);    //для линий
    QPen pen_numbers(QBrush(QColor(0,0,255)), 1);   //для чисел

    int font_size(16);      //параметры шрифта
    float font_aligment(0);
    QFont font_numbers = painter.font();
    font_numbers.setPixelSize(font_size);
    painter.setFont(font_numbers);

    if(m_scale_koef1*m_current_scale/m_scale_koef2 > m_current_default_size*0.1){       //масштабирование размера ячейки
        m_scale_koef1 /= 2;
    } else if(m_scale_koef1*m_current_scale/m_scale_koef2 < m_current_default_size*0.05){
        m_scale_koef1 *= 2;
    }
    double size_of_cell(m_scale_koef1*m_current_scale/m_scale_koef2);

    float center(width()/2);
    int num_on_cell(0);
    painter.setPen(pen_numbers);
    QString num(QString::number(num_on_cell));
    painter.drawText(center + 4, height()/2 - 4, num);
    painter.setPen(pen_lines);
    ++num_on_cell;

    painter.setPen(pen_lines);
    while((center += size_of_cell) < width()){        // отрисовка правых верткальных линий и цифр на координатной оси
        painter.drawLine(center, 0, center, height());
        painter.setPen(pen_numbers);
        num = QString::number(num_on_cell * m_scale_koef1);
        font_aligment = font_size/4 * num.size();
        painter.drawText(center - font_aligment, height()/2 - 4, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    center = width()/2;
    num_on_cell = 1;
    while((center -= size_of_cell) >= 0){           // отрисовка левых вертикальных линий и цифр на координатной оси
        painter.drawLine(center, 0, center, height());
        painter.setPen(pen_numbers);
        num = QString::number(-num_on_cell * m_scale_koef1);
        font_aligment = font_size/4 * num.size();
        painter.drawText(center - font_aligment, height()/2 - 4, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    center = height()/2;
    num_on_cell = 1;
    while((center += size_of_cell) < height()){        // отрисовка нижних горизонтальных линий и цифр на координатной оси
        painter.drawLine(0, center, width(), center);
        painter.setPen(pen_numbers);
        num = QString::number(-num_on_cell * m_scale_koef1);
        font_aligment = font_size/1.4 * num.size();
        painter.drawText(width()/2 - font_aligment, center, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    center = height()/2;
    num_on_cell = 1;
    while((center -= size_of_cell) >= 0){               // отрисовка верхних горизонтальных линий и цифр на координатной оси
        painter.drawLine(0, center, width(), center);
        painter.setPen(pen_numbers);
        num = QString::number(num_on_cell * m_scale_koef1);
        font_aligment = font_size/1.4 * num.size();
        painter.drawText(width()/2 - font_aligment, center, num);
        painter.setPen(pen_lines);
        ++num_on_cell;
    }
    painter.restore();
    //-------------------------------------------------------------     отрисовка графика
    if(!m_points->isEmpty()){
        painter.save();
        painter.setPen(QPen(QBrush(QColor(255,0,0,255)), 3));
        QList<QPair<double, double>>::const_iterator iter = m_points->constBegin();
        painter.drawPoint(width()/2 + m_current_scale/m_scale_koef2 * iter->first, height()/2 + m_current_scale/m_scale_koef2 * iter->second);
        while(iter != m_points->constEnd()-1) {
            ++iter;
            //painter.drawPoint(width()/2 + m_current_scale/m_scale_koef2 * iter->first, height()/2 + m_current_scale/m_scale_koef2 * iter->second);
            painter.drawLine(width()/2 + m_current_scale/m_scale_koef2 * iter->first, height()/2 + m_current_scale/m_scale_koef2 * iter->second, \
                             width()/2 + m_current_scale/m_scale_koef2 * (iter-1)->first, height()/2 + m_current_scale/m_scale_koef2 * (iter-1)->second);
        }
        painter.restore();
    }
    //------------------------------------------------------------- отрисовка вспомогательных линий
    if(m_helpLines_flag){
        painter.save();
        QFont font = painter.font();
        short f_size(13);
        font.setPixelSize(f_size);
        painter.setFont(font);
        painter.setPen(QPen(QBrush(QColor(0,128,225)), 2));

        QPoint coordinates = mapFromGlobal(QCursor::pos());
        double curX((coordinates.x() - width()/2) / (m_current_scale/m_scale_koef2));
        double curY(-1*((coordinates.y() - height()/2) / (m_current_scale/m_scale_koef2)));      

        if(m_is_cartesian){
            painter.drawLine(coordinates.x(), 0, coordinates.x(), height());
            painter.drawLine(0, coordinates.y(), width(), coordinates.y());
            painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + f_size + 2, "x: " + QString::number(curX));
            painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + 2*f_size + 2, "y: " + QString::number(curY));
        }else{
            double r(sqrt(pow(curX, 2) + pow(curY, 2)));
            double phi(acos(curX/r)/M_PI);


            QRect re(width()/2 - 50, height()/2 - 50, 100, 100);

            painter.save();
            painter.setPen(QPen(QBrush(QColor(0, 255, 0)), 3));

            if(curY < 0){
                phi *= -1;
            }
            painter.drawArc(re, 0, phi*180*16);
            if(curY < 0){
                phi *= -1;
            }

            painter.drawLine(width()/2, height()/2, coordinates.x(), coordinates.y());
            painter.restore();

            painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + f_size + 2, "r: " + QString::number(r));
            painter.drawText(coordinates.x() + f_size + 2, coordinates.y() + 2*f_size + 2, "ф: " + QString::number(phi) + "*PI");
        }

        painter.restore();
    }
    //-------------------------------------------------------------
}
