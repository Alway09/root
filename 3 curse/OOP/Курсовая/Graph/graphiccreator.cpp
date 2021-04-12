#include "graphiccreator.h"

const static QString g_tool_tip("\".\" - десятичный разделитель\n\",\" - разделитель порядка");

GraphicCreator::GraphicCreator(QWidget* parent) : QDialog(parent), m_cartesian_graphCB(nullptr), m_save_or_not(new QCheckBox("Сохранить график в файл")),
                                                  m_cartesian_check(new QCheckBox("График в прямоугольных координатах")), m_polar_check(new QCheckBox("График в полярных координатах")),
                                                  m_borders_validator(new QDoubleValidator), m_step_validator(new QDoubleValidator)
{
    initFunctions();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    m_save_or_not->setChecked(false);

    m_cartesian_check->setChecked(true);
    connect(m_cartesian_check, &QCheckBox::stateChanged, this, &GraphicCreator::cartesianChBStateChanged);
    m_polar_check->setChecked(false);
    connect(m_polar_check, &QCheckBox::stateChanged, this, &GraphicCreator::polarChBStateChanged);

    QStringList graph_list1;
    foreach (auto f, m_cartesianFunctions) {
        graph_list1.append(f->getName());
    }
    m_cartesian_graphCB  = new QComboBox;
    m_cartesian_graphCB->addItems(graph_list1);
    m_cartesian_graphCB->setCurrentIndex(0);

    QStringList graph_list2;
    foreach (auto f, m_polarFunctions) {
        graph_list2.append(f->getName());
    }
    m_polar_graphCB = new QComboBox;
    m_polar_graphCB->addItems(graph_list2);
    m_polar_graphCB->setCurrentIndex(0);
    m_polar_graphCB->setDisabled(true);

    QPushButton* openFileBut = new QPushButton("Открыть файл");
    connect(openFileBut, &QPushButton::clicked, this, &GraphicCreator::openFileButtonClicked);

    QLabel* info = new QLabel("Изменять X(ф) в пределах");
    info->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* first = new QHBoxLayout;
    QLabel* ot = new QLabel("От: ");
    QLineEdit* e_ot = new QLineEdit("-10");

    QLabel* doo = new QLabel("До: ");
    QLineEdit* e_doo = new QLineEdit("10");
    m_borders.first = e_ot;
    m_borders.second = e_doo;

    m_borders_validator->setNotation(QDoubleValidator::StandardNotation);
    m_borders_validator->setLocale(QLocale(QLocale::English));
    m_borders.first->setValidator(m_borders_validator);
    m_borders.second->setValidator(m_borders_validator);
    m_borders.first->setToolTip(g_tool_tip);
    m_borders.second->setToolTip(g_tool_tip);

    QHBoxLayout* first1 = new QHBoxLayout;
    QLabel* step = new QLabel("Шаг сетки: ");
    QLineEdit* e_step = new QLineEdit("1");
    m_step = e_step;
    first1->addWidget(step);
    first1->addWidget(e_step);

    m_step_validator->setNotation(QDoubleValidator::StandardNotation);
    m_step_validator->setLocale(QLocale(QLocale::English));
    m_step_validator->setBottom(0);
    m_step_validator->setTop(9);
    m_step->setValidator(m_step_validator);
    m_step->setToolTip(g_tool_tip);

    QHBoxLayout* second = new QHBoxLayout;
    QPushButton* create_b = new QPushButton("Создать");
    connect(create_b, &QPushButton::clicked, this, &GraphicCreator::createButtonClicked);

    QPushButton* back_b = new QPushButton("Назад");
    connect(back_b, &QPushButton::clicked, this, &GraphicCreator::backButtonClicked);
    second->addWidget(create_b);
    second->addWidget(back_b);

    first->addWidget(ot);
    first->addWidget(e_ot);
    first->addWidget(doo);
    first->addWidget(e_doo);

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

    mainLayout->addWidget(openFileBut);
    mainLayout->addWidget(line4);
    mainLayout->addWidget(m_cartesian_check);
    mainLayout->addWidget(m_cartesian_graphCB);
    mainLayout->addWidget(line1);
    mainLayout->addWidget(m_polar_check);
    mainLayout->addWidget(m_polar_graphCB);
    mainLayout->addWidget(line2);
    mainLayout->addWidget(info);
    mainLayout->addLayout(first);
    mainLayout->addLayout(first1);
    mainLayout->addWidget(line3);
    mainLayout->addWidget(m_save_or_not);
    mainLayout->addLayout(second);
    setLayout(mainLayout);
}

GraphicCreator::~GraphicCreator()
{
    delete m_cartesian_graphCB;
    delete m_polar_graphCB;
    delete m_borders.first;
    delete m_borders.second;
    delete m_step;
    delete m_save_or_not;
    delete m_cartesian_check;
    delete m_polar_check;
    delete m_borders_validator;
    delete m_step_validator;

    foreach (auto elem, m_cartesianFunctions) {
        delete elem;
    }

    foreach (auto elem, m_polarFunctions) {
        delete elem;
    }
}

void GraphicCreator::initFunctions(){
    m_cartesianFunctions.append(new f_cos());
    m_cartesianFunctions.append(new f_sin());
    m_cartesianFunctions.append(new f_tg());
    m_cartesianFunctions.append(new f_giperbola1());
    m_cartesianFunctions.append(new f_giperbola2());
    m_cartesianFunctions.append(new f_square_root());
    m_cartesianFunctions.append(new f_parabola());
    m_cartesianFunctions.append(new f_cube_parabola());

    m_polarFunctions.append(new f_spiral_archimeda());
    m_polarFunctions.append(new f_cardioida());
    m_polarFunctions.append(new f_polar_rose1());
    m_polarFunctions.append(new f_polar_rose2());
    m_polarFunctions.append(new f_leminiscate());
    m_polarFunctions.append(new f_pascal_snail());
    m_polarFunctions.append(new f_butterfly());
    m_polarFunctions.append(new f_heart());
}

void GraphicCreator::openFileButtonClicked(){
    QString open_filename = QFileDialog::getOpenFileName(this, "Выберите файл", "./", "Файл JSON (*.json)");
    if(open_filename != ""){
        emit created(open_filename);
        emit to_plane();
    }
}

void GraphicCreator::createButtonClicked(){
    try{
        if(!m_cartesian_check->isChecked() && !m_polar_check->isChecked()){
            throw 1;
        }

        QLocale loc(QLocale::English);
        if(loc.toDouble(m_borders.first->text()) >= loc.toDouble(m_borders.second->text())){
            throw 2;
        }

        if(loc.toDouble(m_step->text()) <= 0){
            throw 3;
        }

        QString save_filename("./temp.json");
        QJsonArray mainArray;

        if(m_cartesian_check->isChecked()){
            QJsonObject obj1;
            obj1["system"] = "C";
            mainArray.append(obj1);

            for(double i = loc.toDouble(m_borders.first->text()); i <= loc.toDouble(m_borders.second->text()); i += loc.toDouble(m_step->text())){
                QPair<double, double> current_point(m_cartesianFunctions[m_cartesian_graphCB->currentIndex()]->getValue(i));
                QJsonObject currentObj;
                currentObj["x"] = current_point.first;
                currentObj["y"] = current_point.second;
                mainArray.append(currentObj);
            }

        } else if(m_polar_check->isChecked()){
            QJsonObject obj2;
            obj2["system"] = "P";
            mainArray.append(obj2);

            for(double i = loc.toDouble(m_borders.first->text()); i <= loc.toDouble(m_borders.second->text()); i += loc.toDouble(m_step->text())){
                QPair<double, double> current_point(m_polarFunctions[m_polar_graphCB->currentIndex()]->getValue(i));
                QJsonObject currentObj;
                currentObj["x"] = current_point.first;
                currentObj["y"] = current_point.second;
                mainArray.append(currentObj);
            }
        }

        if(m_save_or_not->isChecked()){
            save_filename = QFileDialog::getSaveFileName(this, "Выберите папку для сохранения", "./", "Файл JSON (*.json)");

        }

        if(save_filename != ""){
            QFile jsonSaveFile(save_filename);
            if(!jsonSaveFile.open(QIODevice::WriteOnly)){
                return;
            }

            jsonSaveFile.write(QJsonDocument(mainArray).toJson(QJsonDocument::Indented));
            jsonSaveFile.close();
            emit created(save_filename);
            emit to_plane();
        }
    }
    catch(infinity_exeption &ex){
        QMessageBox::warning(this, "Диапазон аргумента", ex.getError());
    }
    catch(borders_exeption &ex){
        QMessageBox::warning(this, "Диапазон аргумента", ex.getError());
    }
    catch(int exeption){
        switch (exeption) {
        case 1:
            QMessageBox::warning(this, "Выбор системы координат", "Выберите одну из предложеных систем координат.");
            break;
        case 2:
            QMessageBox::warning(this, "Границы", "Границы графика заданы некорректно.");
            break;
        case 3:
            QMessageBox::warning(this, "Шаг", "Шаг сетки задан некорректно.");
            break;
        }
    }


}

void GraphicCreator::backButtonClicked(){
    QDialog::accept();
}

void GraphicCreator::cartesianChBStateChanged(int state){
    if(state == 2){
        m_cartesian_graphCB->setDisabled(false);
        m_polar_check->setChecked(false);
        m_polar_graphCB->setDisabled(true);
    }
}

void GraphicCreator::polarChBStateChanged(int state){
    if(state == 2){
        m_cartesian_graphCB->setDisabled(true);
        m_cartesian_check->setChecked(false);
        m_polar_graphCB->setDisabled(false);
    }
}
