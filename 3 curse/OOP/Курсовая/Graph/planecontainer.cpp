#include "planecontainer.h"

#define hsb horizontalScrollBar()
#define vsb verticalScrollBar()

PlaneContainer::PlaneContainer(CoordinatePlane* plane, QWidget* parent) : QScrollArea(parent), m_plane(plane), m_move_point(0, 0), m_is_moving(false), m_plane_helpLinesFlag(false)
{
    setWidget(m_plane);
    m_plane->setDefaultSize(QGuiApplication::screens().at(0)->availableSize().width());
}

PlaneContainer::~PlaneContainer()
{

}

void PlaneContainer::wheelEvent(QWheelEvent *event){
    event->ignore();
}

void PlaneContainer::mousePressEvent(QMouseEvent *event){
    m_move_point.rx() = hsb->value() + event->x();
    m_move_point.ry() = vsb->value() + event->y();
}

void PlaneContainer::mouseMoveEvent(QMouseEvent *event){
    if(!m_plane_helpLinesFlag){
        hsb->setValue(m_move_point.x() - event->x());
        vsb->setValue(m_move_point.y() - event->y());
    }
}

void PlaneContainer::centerize() const{
    hsb->setValue((hsb->maximum() - hsb->minimum())/2);
    vsb->setValue((vsb->maximum() - vsb->minimum())/2);
}

#define mapped widget()->mapFrom(viewport(), QPoint(viewport()->width()/2, viewport()->height()/2))
void PlaneContainer::planeSizeChanged(){
    //int new_value_h(hsb->value()*((float)currentSize/prevSize));
    //int new_value_v(vsb->value()*((float)currentSize/prevSize));

    centerize();

    /*while(mapped.x() != widget()->width()/2){
        if(mapped.x() < widget()->width()/2){
            if(hsb->value() != hsb->maximum()){
                hsb->setValue(hsb->value() + 1);
            } else{
                break;
            }
        } else{
            if(hsb->value() != hsb->minimum()){
                hsb->setValue(hsb->value() - 1);
            } else{
                break;
            }
        }
    }

    while(mapped.y() != widget()->height()/2){
        if(mapped.y() < widget()->height()/2){
            if(vsb->value() != vsb->maximum()){
                vsb->setValue(vsb->value() + 1);
            } else{
                break;
            }
        } else{
            if(vsb->value() != vsb->minimum()){
                vsb->setValue(vsb->value() - 1);
            } else{
                break;
            }
        }
    }*/
}
