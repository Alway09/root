#include "playground.h"

//global vars
static const int default_target_size(15);
static int target_size(default_target_size*0.4);
static bool target_rise_size(true);

static bool on_pause(true);
static bool game_over(false);

static int segments_counter(0);
static int speed(100);
static int move_timer_id(0);
static int target_size_timer_id(0);

Playground::Playground(uint w, uint h, QWidget* parent) : QGraphicsView(), m_snake(), m_head(new Head), m_target(new Target),

    m_points(new QLabel("0", this)), m_pause_labels(new QLabel("PAUSE", this), new QLabel("PRESS SPACE TO CONTINUE OR ESC TO EXIT", this)),

    m_game_over_labels(new QLabel("GAME OVER", this), new QLabel("PRESS SPACE TO PLAY AGAIN\nOR ESC TO RETURN TO MAIN MENU", this)),

    m_width(w), m_heigh(h), m_segments_in_snake(0), m_parent(parent)
{
    setScene(new QGraphicsScene());
    scene()->setSceneRect(0, 0, m_width, m_heigh);
    setFixedSize(m_width, m_heigh);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    placeTarget();

    //m_head->setPos(m_width/2 - m_head->getRadius(), m_heigh/2 - m_head->getRadius());
    m_head->setPos(m_head->getRadius()*2, m_heigh - m_head->getRadius()*2);
    scene()->addItem(m_head);
    scene()->addItem(m_target);
    m_snake.append(m_head);
    segmentsInSnake()++;

    m_points->setFixedWidth(100);
    auto f(m_points->font());
    f.setPixelSize(20);
    m_points->setFont(f);
    m_points->show();

    m_pause_labels.first->setFixedWidth(m_width*0.415);
    f = m_pause_labels.first->font();
    f.setPixelSize(m_width*0.13);
    m_pause_labels.first->setFont(f);
    m_pause_labels.first->setGeometry(m_width/2 - m_pause_labels.first->width()/2, 0, m_width, m_heigh);

    m_pause_labels.second->setFixedWidth(m_width*0.545);
    f = m_pause_labels.second->font();
    f.setPixelSize(m_width*0.025);
    m_pause_labels.second->setFont(f);
    m_pause_labels.second->setGeometry(m_width/2 - m_pause_labels.second->width()/2, m_width*0.06, m_width, m_heigh);

    m_game_over_labels.first->setFixedWidth(m_width*0.75);
    f = m_game_over_labels.first->font();
    f.setPixelSize(m_width*0.13);
    m_game_over_labels.first->setFont(f);
    m_game_over_labels.first->setGeometry(m_width/2 - m_game_over_labels.first->width()/2, 0, m_width, m_heigh);
    m_game_over_labels.first->hide();

    m_game_over_labels.second->setAlignment(Qt::AlignHCenter);
    m_game_over_labels.second->setFixedWidth(m_width*0.545);
    f = m_game_over_labels.second->font();
    f.setPixelSize(m_width*0.025);
    m_game_over_labels.second->setFont(f);
    m_game_over_labels.second->setGeometry(m_width/2 - m_game_over_labels.second->width()/2, m_width*0.45, m_width, m_heigh);
    m_game_over_labels.second->hide();
}

Playground::~Playground(){
    while(!m_snake.empty()){
        delete m_snake.last();
        m_snake.removeLast();
    }
    delete m_target;
    delete m_points;
    delete m_pause_labels.first;
    delete m_pause_labels.second;
    delete m_game_over_labels.first;
    delete m_game_over_labels.second;
}

void Playground::respawn(){
    while(!m_snake.empty()){
        scene()->removeItem(m_snake.last());
        delete m_snake.last();
        m_snake.removeLast();
    }
    //m_snake.clear();
    m_head = new Head;
    scene()->addItem(m_head);
    m_snake.append(m_head);
    segmentsInSnake() = 1;
    segments_counter = 0;

    m_points->setText("0");

    m_head->setPos(m_head->getRadius()*2, m_heigh - m_head->getRadius()*2);

    placeTarget();
    scene()->update(0, 0, m_width, m_heigh);
    moving();
}

void Playground::addToSnake(AbstractSegment *elem, int posx, int posy){
    auto d = m_points->text().toInt();
    m_points->setNum(d+1);

    scene()->addItem(elem);
    elem->setPos(posx, posy);
    m_snake.append(elem);
    segmentsInSnake()++;
    killTimer(move_timer_id);
    move_timer_id = startTimer(speed/segmentsInSnake());
}

void Playground::setup(){
    for(int i = 0; i < 11; ++i){
        Body* a = new Body(m_head->getOrient());
        addToSnake(a, m_snake.back()->x(), m_snake.back()->y() + a->getRadius());
    }
    stop();
}

void Playground::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key::Key_W:
        if(!on_pause){
            if(m_head->getOrient() != DOWN){
                m_head->setOrient(UP);
            }
        }
        m_head->justTurned() = true;
        break;

    case Qt::Key::Key_S:
        if(!on_pause){
            if(m_head->getOrient() != UP){
                m_head->setOrient(DOWN);
            }
        }
        m_head->justTurned() = true;
        break;

    case Qt::Key::Key_A:
        if(!on_pause){
            if(m_head->getOrient() != RIGHT){
                m_head->setOrient(LEFT);
            }
        }
        m_head->justTurned() = true;
        break;

    case Qt::Key::Key_D:
        if(!on_pause){
            if(m_head->getOrient() != LEFT){
                m_head->setOrient(RIGHT);
            }
        }
        m_head->justTurned() = true;
        break;

    case Qt::Key::Key_Space:
        if(!game_over){
            if(on_pause){
                moving();
                m_pause_labels.first->hide();
                m_pause_labels.second->hide();
                on_pause = false;
            } else{
                stop();
                m_pause_labels.first->show();
                m_pause_labels.second->show();
                on_pause = true;
            }
        } else{
            respawn();
            m_game_over_labels.first->hide();
            m_game_over_labels.second->hide();
        }
        break;

    case Qt::Key::Key_Escape:
        if(!game_over){
            if(on_pause){
                close();
            }
        } else{
            m_parent->show();
            close();
        }
        break;
    default:
        break;
    }
}

void Playground::moving(){
    move_timer_id = startTimer(speed/segmentsInSnake());
    target_size_timer_id = startTimer(30);
}

void Playground::stop(){
    killTimer(move_timer_id);
    killTimer(target_size_timer_id);
}

void Playground::timerEvent(QTimerEvent *timer){
    if(timer->timerId() == target_size_timer_id){
        if(target_rise_size){
            ++target_size;
            m_target->moveBy(-0.5, -0.5);
            if(target_size >= default_target_size){
                target_rise_size = false;
            }
        } else{
            --target_size;
            m_target->moveBy(0.5, 0.5);
            if(target_size <= default_target_size*0.4){
                target_rise_size = true;
            }
        }
        m_target->setRadius(target_size);
        scene()->update(0, 0, m_width, m_heigh);
    }

    if(timer->timerId() == move_timer_id){
        int shift(20);
        QList<AbstractSegment*>::iterator iter(m_snake.begin());

        if((*(iter + segments_counter)) != m_head){
            auto temp(static_cast<Body*>((*(iter + segments_counter))));
            //temp->previouseOrient() = temp->getOrient();
            if(temp->stepToTurn()){
                temp->setOrient((*(iter + segments_counter - 1))->previouseOrient());
                temp->stepToTurn() = false;
                temp->justTurned() = true;
            }
        }

        switch ((*(iter + segments_counter))->getOrient()){
        case UP:
            (*(iter + segments_counter))->moveBy(0, -shift);
            break;
        case DOWN:
            (*(iter + segments_counter))->moveBy(0, shift);
            break;
        case LEFT:
            (*(iter + segments_counter))->moveBy(-shift, 0);
            break;
        case RIGHT:
            (*(iter + segments_counter))->moveBy(shift, 0);
            break;
        }
        (*(iter + segments_counter))->previouseOrient() = (*(iter + segments_counter))->getOrient();

        if((*(iter + segments_counter)) != m_head){
            if((*(iter + segments_counter - 1))->justTurned()){
                auto temp(static_cast<Body*>((*(iter + segments_counter))));
                temp->stepToTurn() = true;
                (*(iter + segments_counter - 1))->justTurned() = false;
            }
        }

        scene()->update(0, 0, m_width, m_heigh);
        if((segments_counter + 1) == segmentsInSnake()){
            segments_counter = 0;
        } else{
            segments_counter++;
        }

        if(m_head->collidesWithItem(m_target)){
            placeTarget();

            Body* a;
            if(m_snake.size() == 1){
                a = new Body(m_head->getOrient());
            } else{
                a = new Body(*static_cast<Body*>(m_snake.last()));
            }

            switch(m_snake.back()->getOrient()){
            case UP:
                addToSnake(a, m_snake.back()->x(), m_snake.back()->y() + a->getRadius());
                break;
            case DOWN:
                addToSnake(a, m_snake.back()->x(), m_snake.back()->y() - a->getRadius());
                break;
            case LEFT:
                addToSnake(a, m_snake.back()->x() + a->getRadius(), m_snake.back()->y());
                break;
            case RIGHT:
                addToSnake(a, m_snake.back()->x() - a->getRadius(), m_snake.back()->y());
                break;
            }
        }

        //if((*(iter + segments_counter)) == m_head){
            QList<AbstractSegment*>::iterator it(m_snake.begin() + 1);
            while(it != m_snake.end()){
                if(m_head->collidesWithItem(*it)){
                    stop();
                    game_over = true;
                    m_game_over_labels.first->show();
                    m_game_over_labels.second->show();
                }
                ++it;
            }
        //}
    }
    //update(0, 0, m_width, m_heigh);
}

void Playground::placeTarget() const{
    const quint32 first(m_target->getRadius());
    const quint32 second(m_width - first);
    const quint32 third(m_heigh - first);

    uint f(QRandomGenerator::global()->bounded(first, second));
    uint s(QRandomGenerator::global()->bounded(first, third));

    m_target->setPos(f, s);
}
