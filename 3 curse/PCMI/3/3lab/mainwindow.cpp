#include "mainwindow.h"
#include "ui_mainwindow.h"

const static QStringList color_name_list({"Черный", "Голубой", "Синий", "Темно-синий", "Фиолетовый", "Фуксин", "Красный", "Бордовый",
                                     "Желтый", "Белый", "Серебряный", "Серый", "Серо-зеленый", "Зеленый", "Ярко-зеленый", "Оливковый"});

const static QVector<QColor> color_vect({QColor(0, 0, 0), QColor(0,255,255), QColor(0,0,255), QColor(0,0,128), QColor(128,0,128), QColor(255,0,255), QColor(255, 0, 0),
                                        QColor(128, 0, 0), QColor(255, 255, 0), QColor(255, 255, 255), QColor(192, 192, 192), QColor(128, 128, 128), QColor(0, 128, 128),
                                        QColor(0, 128, 0), QColor(0, 255, 0), QColor(128, 128, 0)});

const static QStringList button_position({"Левый верхний угол", "Верх", "Правый верхний угол", "Право", "Правый нижний угол", "Низ", "Левый нижний угол", "Лево"});

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_button(new Button(12, 6, this)), m_button1(new Button1(25, 60, this)), m_zad11workArea(new WorkArea), m_S_LE(new QLineEdit("50")),
      m_D_LE(new QLineEdit("6")), m_h_LE(new QLineEdit("0")), m_filename(new QLineEdit("Задание 1.1")), m_results(new QTextEdit), m_first_exp(new QCheckBox("Задание 1")),
      m_second_exp(new QCheckBox("Задание 2")), m_third_exp1(new QCheckBox("Задание 3")), m_fourth_exp1(new QCheckBox("Задание 4.1")),
      m_fourth_exp2(new QCheckBox("Задание 4.2")), m_bg_colors_CB(new QComboBox),m_but_colors_CB(new QComboBox),m_button_pos(new QComboBox),
      m_distance(50), m_timer_id(-1), m_milliseconds(0), m_counter(0), m_missing_counter(0), m_top_exp(10), m_average_time(0)
{
    ui->setupUi(this);

    m_first_exp->setChecked(true);
    m_bg_colors_CB->addItems(color_name_list);
    m_bg_colors_CB->setCurrentIndex(11);
    m_but_colors_CB->addItems(color_name_list);
    m_but_colors_CB->setCurrentIndex(7);
    m_button_pos->addItems(button_position);
    m_button_pos->setCurrentIndex(0);
    m_button_pos->setDisabled(true);

    connect(m_button, &Button::onButtonClicked, this, &MainWindow::trigger_buttonClicked);
    connect(m_button1, &Button1::onButtonClicked, this, &MainWindow::trigger_buttonClicked);
    connect(m_zad11workArea, &WorkArea::onAreaMousePressed, this, &MainWindow::workArea_mouseClicked);
    connect(m_first_exp, &QCheckBox::stateChanged, this, &MainWindow::firstExpCheckChanged);
    connect(m_second_exp, &QCheckBox::stateChanged, this, &MainWindow::secondExpCheckChanged);
    connect(m_third_exp1, &QCheckBox::stateChanged, this, &MainWindow::thirdExp1CheckChanged);
    connect(m_fourth_exp1, &QCheckBox::stateChanged, this, &MainWindow::fourthExp1CheckChanged);
    connect(m_fourth_exp2, &QCheckBox::stateChanged, this, &MainWindow::fourthExp2CheckChanged);

    QHBoxLayout* zad11Lay = new QHBoxLayout;
    QHBoxLayout* first = new QHBoxLayout;
    QHBoxLayout* second = new QHBoxLayout;
    QHBoxLayout* third = new QHBoxLayout;
    QHBoxLayout* fourth = new QHBoxLayout;
    QHBoxLayout* fifth = new QHBoxLayout;
    QHBoxLayout* sixth = new QHBoxLayout;
    QHBoxLayout* seventh = new QHBoxLayout;

    QLabel* s_l = new QLabel("S: ");
    s_l->setAlignment(Qt::AlignHCenter);
    s_l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* d_l = new QLabel("D: ");
    d_l->setAlignment(Qt::AlignHCenter);
    d_l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* h_l = new QLabel("H: ");
    h_l->setAlignment(Qt::AlignHCenter);
    h_l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* but_col_l = new QLabel("Кнопка: ");
    QLabel* bg_col_l = new QLabel("Фон: ");

    QLabel* but_pos = new QLabel("Позиция кнопки: ");

    QLabel* file_l = new QLabel("Имя файла: ");
    file_l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_filename->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_S_LE->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_D_LE->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_h_LE->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_h_LE->setDisabled(true);

    QPushButton* s_button = new QPushButton("Применить");
    s_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(s_button, &QPushButton::clicked, this, &MainWindow::s_buttonClicked);

    QPushButton* clear_button = new QPushButton("Очистить");
    clear_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(clear_button, &QPushButton::clicked, this, &MainWindow::clear_buttonClicked);

    QPushButton* save_button = new QPushButton("Сохранить");
    save_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(save_button, &QPushButton::clicked, this, &MainWindow::save_buttonClicked);

    m_results->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_results->append("Нажмите \"R(англ.)\" чтобы начать");
    m_results->append("Результаты:");

    QFrame* line1 = new QFrame;
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    QFrame* line2 = new QFrame;
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    QFrame* line3 = new QFrame;
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);

    QFrame* line4 = new QFrame;
    line4->setFrameShape(QFrame::HLine);
    line4->setFrameShadow(QFrame::Sunken);

    QFrame* line5 = new QFrame;
    line5->setFrameShape(QFrame::HLine);
    line5->setFrameShadow(QFrame::Sunken);

    QFrame* line6 = new QFrame;
    line6->setFrameShape(QFrame::HLine);
    line6->setFrameShadow(QFrame::Sunken);
    line6->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QFrame* line7 = new QFrame;
    line7->setFrameShape(QFrame::HLine);
    line7->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* s_lay = new QVBoxLayout;
    s_lay->addWidget(line7);
    first->addWidget(s_l);
    first->addWidget(m_S_LE);
    s_lay->addLayout(first);
    second->addWidget(d_l);
    second->addWidget(m_D_LE);
    s_lay->addLayout(second);
    fifth->addWidget(h_l);
    fifth->addWidget(m_h_LE);
    s_lay->addLayout(fifth);
    s_lay->addWidget(line1);
    third->addWidget(but_col_l);
    third->addWidget(m_but_colors_CB);
    s_lay->addLayout(third);
    fourth->addWidget(bg_col_l);
    fourth->addWidget(m_bg_colors_CB);
    s_lay->addLayout(fourth);
    sixth->addWidget(but_pos);
    sixth->addWidget(m_button_pos);
    s_lay->addLayout(sixth);
    s_lay->addWidget(line2);
    s_lay->addWidget(m_first_exp);
    s_lay->addWidget(m_second_exp);
    s_lay->addWidget(m_third_exp1);
    s_lay->addWidget(m_fourth_exp1);
    s_lay->addWidget(m_fourth_exp2);
    s_lay->addWidget(line3);
    s_lay->addWidget(s_button);
    s_lay->addWidget(line4);
    s_lay->addWidget(m_results);
    s_lay->addWidget(clear_button);
    s_lay->addWidget(line5);
    seventh->addWidget(file_l);
    seventh->addWidget(m_filename);
    s_lay->addLayout(seventh);
    s_lay->addWidget(save_button);
    s_lay->addWidget(line6);
    s_lay->setAlignment(Qt::AlignTop);

    QVBoxLayout* zad11workArea_lay = new QVBoxLayout;
    zad11workArea_lay->addWidget(m_button);
    zad11workArea_lay->addWidget(m_button1);
    m_zad11workArea->setLayout(zad11workArea_lay);


    zad11Lay->addWidget(m_zad11workArea);
    zad11Lay->addLayout(s_lay);

    QWidget* central_w = new QWidget;
    central_w->setLayout(zad11Lay);
    setCentralWidget(central_w);
    m_button->hide();
    m_button1->hide();
    m_zad11workArea->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R){
        /*if(m_third_exp1->isChecked()){
            int current_color(QRandomGenerator::global()->bounded(15));
            while(true){
                if(current_color == m_but_colors_CB->currentIndex()){
                    current_color = QRandomGenerator::global()->bounded(0, 15);
                } else{
                    m_bg_colors_CB->setCurrentIndex(current_color);
                    setAreaColor(current_color);
                    break;
                }
            }
        } else if(m_third_exp2->isChecked()){
            int current_color(QRandomGenerator::global()->bounded(15));
            while(true){
                if(current_color == m_bg_colors_CB->currentIndex()){
                    current_color = QRandomGenerator::global()->bounded(0, 15);
                } else{
                    m_but_colors_CB->setCurrentIndex(current_color);
                    setButtonColor(current_color);
                    break;
                }
            }
        }*/

        if(m_first_exp->isChecked() || m_second_exp->isChecked() || m_third_exp1->isChecked()){
            m_zad11workArea->setMouseTracking(false);
            cursor().setPos(m_zad11workArea->mapToGlobal(QPoint(m_zad11workArea->width()/2, m_zad11workArea->height()/2)));
            m_button->show();
            m_button1->hide();
            placeButton(m_button, m_zad11workArea);
        } else if(m_fourth_exp1->isChecked() || m_fourth_exp2->isChecked()){
            if(m_fourth_exp1->isChecked()){
                m_zad11workArea->setMouseTracking(false);
            }
            if(m_fourth_exp2->isChecked()){
                m_zad11workArea->setMouseTracking(true);
            }
            m_button->hide();
            m_button1->show();
            placeButton1(m_button1, m_zad11workArea);
        }
    }
}

void MainWindow::placeButton(Button *b, WorkArea* area){
        double pi(3.14159);
        double angle(QRandomGenerator::global()->bounded(2*pi));
        //double angle(pi*3/2);

        int k_height(0), k_width(0);
        if(m_distance > 0){
            if(angle >= 0 && angle < pi/2){
                k_height = 0;
                k_width = 0;
            } else if(angle >= pi/2 && angle < pi){
                k_height = b->height();
                k_width = 0;
            } else if(angle >= pi && angle < pi*3/2){
                k_height = -b->height();
                k_width = -b->width();
            } else if(angle >= pi*3/2 && angle <= 2*pi){
                k_height = -b->height();
                k_width = 0;
            }
        }

        b->move(k_width + area->mapFromGlobal(cursor().pos()).x() + m_distance*cos(angle), k_height + area->mapFromGlobal(cursor().pos()).y() + m_distance*sin(angle));
        //qDebug() << k_height << " " << k_width ;

        if(m_timer_id == -1){
            m_timer_id = startTimer(1);
        } else{
            killTimer(m_timer_id);
            m_timer_id = startTimer(1);
            m_milliseconds = 0;
        }

        qDebug() << b->pos().x() << b->pos().y();
}

void MainWindow::placeButton1(Button1 *b, WorkArea *area){
    double pi(3.14159);
    double angle1(QRandomGenerator::global()->bounded(pi));
    double angle2(QRandomGenerator::global()->bounded(pi/2));
    const int a(60);
    const int o(5);

    static bool flag(true);

    int k_height(-1 * b->height()/2), k_width(b->width()/2);
    if(m_distance > 0){
        if(angle1 >= pi/2){
            k_height *= -1;
            k_width *= -1;
        }
    }

    if(m_fourth_exp1->isChecked()){
        if(flag){
            b->move(m_h_LE->text().toInt(), area->height()/2 - b->height()/2);
            cursor().setPos(area->mapToGlobal(QPoint(b->width() + m_distance*cos(angle1 - pi/2) + m_h_LE->text().toInt(), k_height + area->height()/2 + m_distance*sin(angle1 - pi/2))));
            flag = false;
        } else{
            b->move(area->width() - b->width() - m_h_LE->text().toInt(), area->height()/2 - b->height()/2);
            cursor().setPos(area->mapToGlobal(QPoint(area->width() - b->width() - m_distance*cos(angle1 - pi/2) - m_h_LE->text().toInt(), k_height + area->height()/2 + m_distance*sin(angle1 - pi/2))));
            flag = true;
        }
    } else if(m_fourth_exp2->isChecked()){
        switch (m_button_pos->currentIndex()) {
        case 0:
            b->move(a - o, a - o);
            cursor().setPos(area->mapToGlobal(QPoint(b->width() + a - o + m_distance*cos(angle2), b->height() + a - o + m_distance*sin(angle2))));
            break;
        case 1:
            b->move(area->width()/2 - b->width()/2, a - o);
            cursor().setPos(area->mapToGlobal(QPoint(area->width()/2 + k_width + m_distance*cos(angle1),b->height() + a - o + m_distance*sin(angle1))));
            break;
        case 2:
            b->move(area->width() - b->width() - a + o, a - o);
            cursor().setPos(area->mapToGlobal(QPoint(area->width() - b->width() - a + o - m_distance*cos(angle2), b->height() + a - o + m_distance*sin(angle2))));
            break;
        case 3:
            b->move(area->width() - b->width() - a + o, area->height()/2 - b->height()/2);
            cursor().setPos(area->mapToGlobal(QPoint(area->width() - b->width() - m_distance*cos(angle1 - pi/2) - a + o, k_height + area->height()/2 + m_distance*sin(angle1 - pi/2))));
            break;
        case 4:
            b->move(area->width() - b->width() - a + o, area->height() - b->height() - a + o);
            cursor().setPos(area->mapToGlobal(QPoint(area->width() - b->width() - a + o - m_distance*cos(angle2 - pi/2),area->height() - b->height() - a + o + m_distance*sin(angle2 - pi/2))));
            break;
        case 5:
            b->move(area->width()/2 - b->width()/2, area->height() - b->height() - a + o);
            cursor().setPos(area->mapToGlobal(QPoint(area->width()/2 - k_width + m_distance*cos(angle1 + pi),area->height() - b->height() - a + o + m_distance*sin(angle1 + pi))));
            break;
        case 6:
            b->move(a - o, area->height() - b->height() - a + o);
            cursor().setPos(area->mapToGlobal(QPoint(b->width() + a - o + m_distance*cos(angle2 - pi/2),area->height() - b->height() - a + o + m_distance*sin(angle2 - pi/2))));
            break;
        case 7:
            b->move(a - o, area->height()/2 - b->height()/2);
            cursor().setPos(area->mapToGlobal(QPoint(b->width() + m_distance*cos(angle1 - pi/2) + a - o, k_height + area->height()/2 + m_distance*sin(angle1 - pi/2))));
            break;
        }
    }


    if(m_timer_id == -1){
        m_timer_id = startTimer(1);
    } else{
        killTimer(m_timer_id);
        m_timer_id = startTimer(1);
        m_milliseconds = 0;
    }
}

void MainWindow::s_buttonClicked(){   
    if(m_but_colors_CB->currentIndex() != m_bg_colors_CB->currentIndex()){
        setButtonColor(m_but_colors_CB->currentIndex());
        setAreaColor(m_bg_colors_CB->currentIndex());
    } else{
        setAreaColor(m_bg_colors_CB->currentIndex());
        QMessageBox::warning(this, "Цвета", "Необходимо выбрать разные цвета фона и кнопки!");
        for(int i = 0; i < 16; ++i){
            if(i != m_bg_colors_CB->currentIndex()){
                setButtonColor(i);
                m_but_colors_CB->setCurrentIndex(i);
                break;
            }
        }
    }

    if(m_S_LE->text().toInt() >= 0 && m_S_LE->text().toInt() <= 450){
        m_distance = m_S_LE->text().toInt();
    } else{
        QMessageBox::warning(this, "Расстояние", "Расстояние задано некорректно!");
        m_S_LE->setText("0");
        m_distance = 0;
    }

    if(m_D_LE->text().toInt() > 0 && m_D_LE->text().toInt() <= 100){
        if(m_first_exp->isChecked() || m_second_exp->isChecked()){
            m_button->setSize(2*m_D_LE->text().toInt(), m_D_LE->text().toInt());
        } else if(m_third_exp1->isChecked()){
            m_button->setSize(3.5*m_D_LE->text().toInt(), m_D_LE->text().toInt());
        }
    }else{
        QMessageBox::warning(this, "Размер", "Размер задан некорректно!");
        m_D_LE->setText("6");
        if(m_first_exp->isChecked() || m_second_exp->isChecked()){
            m_button->setSize(2*m_D_LE->text().toInt(), m_D_LE->text().toInt());
        } else if(m_third_exp1->isChecked()){
            m_button->setSize(3.5*m_D_LE->text().toInt(), m_D_LE->text().toInt());
        }
    }


    if(!(m_first_exp->isChecked() || m_second_exp->isChecked() || m_third_exp1->isChecked() || m_fourth_exp1->isChecked() || m_fourth_exp2->isChecked())){
        QMessageBox::warning(this, "Задание", "Необходимо выбрать хотя бы одно задание!");
        m_first_exp->setChecked(true);
    }

    //if(m_first_exp->isChecked() || m_second_exp->isChecked() || m_third_exp1->isChecked() || m_third_exp2->isChecked() || m_fourth_exp1->isChecked()){
        //m_button->setSize(2*m_D_LE->text().toInt(), m_D_LE->text().toInt());

    //}

    /*if(m_third_exp1->isChecked() || m_third_exp2->isChecked()){
        m_button->setSize(3.5*m_D_LE->text().toInt(), m_D_LE->text().toInt());
        setButtonColor(m_but_colors_CB->currentIndex());
        setAreaColor(m_bg_colors_CB->currentIndex());

    }*/

    if(m_fourth_exp1->isChecked() || m_fourth_exp2->isChecked()){
        m_button1->setSize(25, 60);
        //setButtonColor(m_but_colors_CB->currentIndex());
        //setAreaColor(m_bg_colors_CB->currentIndex());
    }

    if(m_counter != 0){
        m_results->append("Среднее время: " + QString::number((m_average_time/1000.0)/m_counter) + "сек");
    }
    m_average_time = 0;
    m_results->append("----------------");
    m_counter = 0;
    m_missing_counter = 0;
    //m_button->hide();
}

void MainWindow::timerEvent(QTimerEvent *timer){
    if(timer->timerId() == m_timer_id){
        ++m_milliseconds;
    }
    if(m_second_exp->isChecked() && m_milliseconds == 1500){
        workArea_mouseClicked(true);
    }
}

void MainWindow::trigger_buttonClicked(){
    m_zad11workArea->setMouseTracking(false);
    if(m_timer_id >= 0){
        killTimer(m_timer_id);
        m_average_time += m_milliseconds;
        m_timer_id = -1;
        ++m_counter;
        if(m_counter == 1 && m_missing_counter == 0){
            if(m_first_exp->isChecked()){
                m_results->append("S=" + m_S_LE->text() + ", D=" + m_D_LE->text());
            }
            //if(m_first_exp->isChecked() || m_second_exp->isChecked() || m_third_exp1->isChecked() ){
                m_results->append("Цвет кнопки: " + color_name_list[m_but_colors_CB->currentIndex()]);
                m_results->append("Цвет фона: " + color_name_list[m_bg_colors_CB->currentIndex()]);
            //}
            if(m_fourth_exp2->isChecked()){
                m_results->append("Позиция кнопки: " + button_position[m_button_pos->currentIndex()]);
            }
            if(m_first_exp->isChecked()){
                m_results->append("S/D=" + QString::number(m_S_LE->text().toFloat()/m_D_LE->text().toFloat()));
            }
        }

        m_results->append(QString::number(m_counter) + ". " + QString::number(m_milliseconds/1000.0) + "сек");
        /*if(m_first_exp->isChecked() || m_second_exp->isChecked() || m_fourth_exp1->isChecked() || m_fourth_exp2->isChecked()){
            m_results->append(QString::number(m_counter) + ". " + QString::number(m_milliseconds/1000.0) + "сек");
        } else if(m_third_exp1->isChecked()){
            m_results->append(QString::number(m_counter) + ". " + QString::number(m_milliseconds/1000.0) + "сек (Фон: " + color_name_list[m_bg_colors_CB->currentIndex()] + ")");
        } else if(m_third_exp2->isChecked()){
            m_results->append(QString::number(m_counter) + ". " + QString::number(m_milliseconds/1000.0) + "сек (Кнопка: " + color_name_list[m_but_colors_CB->currentIndex()] + ")");
        }*/

        if(m_counter == m_top_exp){
            m_counter = 0;
            m_missing_counter = 0;
            m_results->append("Среднее время: " + QString::number((m_average_time/1000.0)/m_top_exp) + "сек");
            m_average_time = 0;
            m_results->append("----------------");
        }
        m_milliseconds = 0;
    }
}

void MainWindow::workArea_mouseClicked(bool late){
    m_zad11workArea->setMouseTracking(false);
    if(m_timer_id >= 0){
        killTimer(m_timer_id);
        m_timer_id = -1;
        if(m_missing_counter == 0 && m_counter == 0){
            if(m_first_exp->isChecked()){
                m_results->append("S=" + m_S_LE->text() + ", D=" + m_D_LE->text());
            }
            m_results->append("Цвет кнопки: " + color_name_list[m_but_colors_CB->currentIndex()]);
            m_results->append("Цвет фона: " + color_name_list[m_bg_colors_CB->currentIndex()]);
            if(m_first_exp->isChecked()){
                m_results->append("S/D=" + QString::number(m_S_LE->text().toFloat()/m_D_LE->text().toFloat()));
            }
        }
        if(!late){
            ++m_missing_counter;
            m_results->append("X. " + QString::number(m_milliseconds/1000.0) + "сек (" + QString::number(m_missing_counter) + " пропуск)");
        } else{
            m_results->append("X. " + QString::number(m_milliseconds/1000.0) + "сек (ОПОЗДАНИЕ)");
        }

        m_milliseconds = 0;
    }
}

void MainWindow::clear_buttonClicked(){
    m_results->clear();
    m_results->append("Нажмите \"R\" чтобы начать");
    m_results->append("Результаты:");
}

void MainWindow::firstExpCheckChanged(int state){
    if(state == 2){
        m_second_exp->setChecked(false);
        m_third_exp1->setChecked(false);
        m_fourth_exp1->setChecked(false);
        m_fourth_exp2->setChecked(false);
        m_but_colors_CB->setDisabled(false);
        m_bg_colors_CB->setDisabled(false);
        m_button_pos->setDisabled(true);
        m_h_LE->setDisabled(true);
    }
}

void MainWindow::secondExpCheckChanged(int state){
    if(state == 2){
        m_first_exp->setChecked(false);
        m_third_exp1->setChecked(false);
        m_fourth_exp1->setChecked(false);
        m_fourth_exp2->setChecked(false);
        m_but_colors_CB->setDisabled(false);
        m_bg_colors_CB->setDisabled(false);
        m_button_pos->setDisabled(true);
        m_h_LE->setDisabled(true);
    }
}

void MainWindow::thirdExp1CheckChanged(int state){
    if(state == 2){
        m_first_exp->setChecked(false);
        m_second_exp->setChecked(false);
        m_fourth_exp1->setChecked(false);
        m_fourth_exp2->setChecked(false);
        m_but_colors_CB->setDisabled(false);
        //m_bg_colors_CB->setDisabled(true);
        m_button_pos->setDisabled(true);
        m_h_LE->setDisabled(true);
    }
}

void MainWindow::fourthExp1CheckChanged(int state){
    if(state == 2){
        m_first_exp->setChecked(false);
        m_second_exp->setChecked(false);
        m_third_exp1->setChecked(false);
        m_fourth_exp2->setChecked(false);
        m_but_colors_CB->setDisabled(false);
        m_bg_colors_CB->setDisabled(false);
        m_button_pos->setDisabled(true);
        m_h_LE->setDisabled(false);
    }
}

void MainWindow::fourthExp2CheckChanged(int state){
    if(state == 2){
        m_first_exp->setChecked(false);
        m_second_exp->setChecked(false);
        m_third_exp1->setChecked(false);
        m_fourth_exp1->setChecked(false);
        m_but_colors_CB->setDisabled(false);
        m_bg_colors_CB->setDisabled(false);
        m_button_pos->setDisabled(false);
        m_h_LE->setDisabled(true);
    }
}

void MainWindow::setButtonColor(int index){
    m_button->setColor(color_vect[index]);
    m_button1->setColor(color_vect[index]);
}

void MainWindow::setAreaColor(int index){
    m_zad11workArea->setColor(color_vect[index]);
}

void MainWindow::save_buttonClicked(){
    if(m_filename->text() != ""){
        QFile file("../" + m_filename->text());
        if(!file.exists()){
            if(file.open(QIODevice::WriteOnly)){
                file.write(m_results->toPlainText().toLocal8Bit());
                QMessageBox::information(this, "Файл", "Файл сохранен как " + file.fileName() + ".");
                file.close();
            } else{
                QMessageBox::critical(this, "Файл", "Не удалось создать файл!");
            }
        } else{
            QMessageBox msg;
            msg.setInformativeText("Файл с таким названием уже существует. Перезаписать?");
            msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
            msg.setDefaultButton(QMessageBox::Save);

            switch (msg.exec()) {
            case QMessageBox::Save:
                if(file.open(QIODevice::WriteOnly)){
                    file.write(m_results->toPlainText().toLocal8Bit());
                    QMessageBox::information(this, "Файл", "Файл сохранен как " + file.fileName() + ".");
                    file.close();
                } else{
                    QMessageBox::critical(this, "Файл", "Не удалось создать файл!");
                }
                break;
            case QMessageBox::Discard:
                break;
            default:
                break;
            }
        }
    }
}
