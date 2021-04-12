#include "method.h"
#include "ui_method.h"
#include<QLineEdit>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QString>
#include<QTextEdit>
#include<QPushButton>
#include<QVector>
#include<cmath>
#include<limits>
#include<QPair>
#include<algorithm>
#include<QLine>
#include<QMessageBox>
#include"matrixd.h"
#include"qcustomplot.h"
#include"scene.h"
#include"node.h"
#include<QGraphicsView>
#include<QGraphicsLineItem>

static QVector<QPair<int,int>> total_path;
static int record = std::numeric_limits<int>::max();

Method::Method(QWidget *parent, int am_of_ci, bool chbx_2) :
    QDialog(parent),
    amount_of_cities(am_of_ci),
    ui(new Ui::Method)
{
    ui->setupUi(this);
    parentWidget()->hide();

    if(!chbx_2){
        QVBoxLayout* mainLay = new QVBoxLayout(this);
        QHBoxLayout* layButtons = new QHBoxLayout();
        QGridLayout* layLines = new QGridLayout();
        QHBoxLayout* layStart = new QHBoxLayout();

        QTextEdit* textEd = new QTextEdit("Введите расстояния  в таблицу");
        textEdit = textEd;

        QLineEdit* start = new QLineEdit;
        start->setText("A");
        start->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        start_point = start;
        QLabel* s_p = new QLabel("Начало маршрута: ");
        s_p->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layStart->addWidget(s_p);
        layStart->addWidget(start);

        QPushButton* calculate = new QPushButton("Рассчитать", this);
        connect(calculate, SIGNAL(clicked()), this, SLOT(calculateButton_clicked()));

        QPushButton* back = new QPushButton("Назад", this);
        back->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(back, SIGNAL(clicked()), this, SLOT(backButtont_clicked()));

        layButtons->addWidget(calculate);
        layButtons->addWidget(back);


        int a_o_c = am_of_ci;
        int letters_c = 65, letters_s = 65;
        char c, s;
        a_o_c++;
        for(int i = 1; i < a_o_c*a_o_c; i++)
        {
            if((i/a_o_c == 0) && (i%a_o_c == 0)){
                c = ' ';
                QLabel* lbl = new QLabel(QString(c));
                layLines->addWidget(lbl, i/a_o_c, i%a_o_c);
                continue;
            }
            if(i/a_o_c == 0){
                c = letters_c;
                QLabel* lbl = new QLabel(QString(c));
                lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                layLines->addWidget(lbl, i/a_o_c, i%a_o_c);
                letters_c++;
                continue;
            }
            if(i%a_o_c == 0){
                s = letters_s;
                QLabel* lbl = new QLabel(QString(s));
                lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                layLines->addWidget(lbl, i/a_o_c, i%a_o_c);
                letters_s++;
                continue;
            }
            QLineEdit* led = new QLineEdit;
            lines_vector.push_back(led);
            layLines->addWidget(led, i/a_o_c, i%a_o_c);
        }

        for(int i = 0; i < a_o_c-1; i++){
            lines_vector[i*a_o_c]->setText("inf");
        }
        mainLay->addWidget(textEd);
        mainLay->addLayout(layStart);
        mainLay->addLayout(layLines);
        mainLay->addLayout(layButtons);
        setLayout(mainLay);
    } else if(chbx_2){
        QHBoxLayout* mainVLayout = new QHBoxLayout(this);
        QVBoxLayout* lay = new QVBoxLayout();
        QHBoxLayout* lay2 = new QHBoxLayout();

        QPushButton* calculate_button = new QPushButton("Рассчитать");
        connect(calculate_button, SIGNAL(clicked()), this, SLOT(calculate_button_clicked()));
        QPushButton* back_button = new QPushButton("Назад");
        connect(back_button, SIGNAL(clicked()), this, SLOT(backButtont_clicked()));
        QPushButton* clear_button = new QPushButton("Очистить");
        connect(clear_button, SIGNAL(clicked()), this, SLOT(clearButtont_clicked()));
        QPushButton* again_button = new QPushButton("Задать вершины заново");
        connect(again_button, SIGNAL(clicked()), this, SLOT(againButtont_clicked()));

        QTextEdit* txEd = new QTextEdit();
        txEd->setMinimumWidth(300);
        txEd->setMaximumWidth(300);
        txEd->append("ПКМ - создать вершину");
        txEd->append("ПКМ по вершине - удалить вершину");
        txEd->append("ЛКМ по вершине + вести - переместить вершину");
        textEdit = txEd;


        Scene* sc = new Scene(mainVLayout);
        sc->setSceneRect(0,0, 490,490);
        scene = sc;
        QGraphicsView* vi = new QGraphicsView(sc);
        vi->setMinimumSize(500,500);
        view = vi;

        lay->addWidget(calculate_button);
        lay2->addWidget(clear_button);
        lay2->addWidget(again_button);
        lay->addLayout(lay2);
        lay->addWidget(txEd);
        lay->addWidget(back_button);
        mainVLayout->addWidget(vi);
        mainVLayout->addLayout(lay);
        setLayout(mainVLayout);

    }
}

Method::~Method()
{
    delete ui;
}

void Method::backButtont_clicked(){
    Node::id = 1;
    parentWidget()->show();
    this->close();
}

void Method::commivoyager(MatrixD matrix){
    if(matrix.get_matrix_size() == 2){
        matrix.last_transform(amount_of_cities);
        if(matrix.get_bottomLimit() < record){
            total_path = matrix.get_path();
            record = matrix.get_bottomLimit();
            return;
        } else{
            return;
        }
    }

    auto edge(matrix.edge());

    auto matrix_cpy1(matrix);
    auto matrix_cpy2(matrix);

    matrix_cpy1.add_to_path({matrix_cpy1.get_str_num(edge.first), matrix_cpy1.get_col_num(edge.second)});
    if(!matrix_cpy1.check_path_right()){
        return;
    }
    matrix_cpy1.reduction(edge.first, edge.second);
    matrix_cpy1.inf_return_trip();
    if(matrix_cpy1.all_inf()){
        return;
    }
    matrix_cpy1.set_bottomLimit(matrix.get_bottomLimit() + matrix_cpy1.sum_of_const());
    if(matrix_cpy1.get_bottomLimit() > record){
        return;
    } else{
        commivoyager(matrix_cpy1);
    }


    matrix_cpy2.add_inf(edge.first, edge.second);
    if(matrix_cpy2.all_inf()){
        return;
    }
    matrix_cpy2.set_bottomLimit(matrix.get_bottomLimit() + matrix_cpy2.sum_of_const());
    if(matrix_cpy2.get_bottomLimit() > record){
        return;
    } else{
        commivoyager(matrix_cpy2);
    }
}


void Method::calculateButton_clicked(){
    QVector<QVector<QPair<int, QString>>> m(amount_of_cities, QVector<QPair<int,QString>>(amount_of_cities, {0, "0"}));
    QVector<int> table(amount_of_cities);
    for(int i = 0; i < amount_of_cities; i++){
        table[i] = i;
    }
    int counter = 0;
    for(int i = 0; i < amount_of_cities; i++){
        for(int j = 0; j < amount_of_cities; j++){
            if(lines_vector[counter]->text() != "inf"){
                m[i][j].first = lines_vector[counter]->text().toInt();
                counter++;
            } else{
                m[i][j].second = "inf";
                counter++;
            }
        }
    }

    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m.size(); j++){
            if(m[i][j].first == 0 && i != j){
                QMessageBox::warning(this, "Нулевое расстояние", "В одной из ячеек матрицы расстояний находится ноль,\nлибо одна из ячеек пуста.");
                return;
            }
        }
    }

    MatrixD matrix(m, table, table);
    matrix.set_bottomLimit(matrix.sum_of_const());
    commivoyager(matrix);
    std::string s = start_point->text().toStdString();

    const char* start = s.c_str();
    int c = 65, remember_i = -1;
    QVector<char> alphabet;
    for(int i = 0; i < amount_of_cities; i++){
        alphabet.push_back(c);
        if(c == std::toupper(*start)) remember_i = i;
        c++;
    }

    if(remember_i == -1){
        QMessageBox::warning(this, "Начало пути", "Заданное начало пути не найдено.\nНачало пути принято за \"A\".");
        remember_i = 0;
    }

    QVector<char> result;
    result.push_back(alphabet[remember_i]);
    while(!total_path.isEmpty()){
        for(int i = 0; i < total_path.size(); i++){
            if(total_path[i].first == remember_i){
                remember_i = total_path[i].second;
                result.push_back(alphabet[remember_i]);
                total_path.remove(i);
            }
        }
    }

    textEdit->clear();
    textEdit->append("Путь: ");
    for(int i = 0; i < result.size()-1; i++){

        textEdit->insertPlainText(QString(result[i]) + "->");
    }
    textEdit->insertPlainText(QString(result[result.size()-1]));

    textEdit->append("Вес пути: " + QString::number(record));
    record = std::numeric_limits<int>::max();
}

void Method::calculate_button_clicked(){
    if(scene->getNodesAmount() < 3){
        QMessageBox::critical(this, "Вершины", "Путь не может состоять из менее чем трех вершин");
        return;
    }
    for(size_t i = 0; i < scene->getNodesAmount(); i++){
        for(size_t j = 0; j < scene->getNodesAmount(); j++){
            if(i != j)
                if(scene->getNode(i)->collidesWithItem(scene->getNode(j))){
                    QMessageBox::warning(this, "Пересечения", "Имеются пересекающиеся вершины.");
                    return;
                }
        }
    }
    view->setEnabled(false);
    amount_of_cities = scene->getNodesAmount();
    QVector<QVector<QPair<int, QString>>> m(amount_of_cities, QVector<QPair<int,QString>>(amount_of_cities, {0, "0"}));
    QVector<int> table(amount_of_cities);
    for(int i = 0; i < amount_of_cities; i++){
        table[i] = i;
    }
    for(int i = 0; i < amount_of_cities; i++){
        for(int j = 0; j < amount_of_cities; j++){
            if(i == j){
                m[i][j].second = "inf";
            } else{
                m[i][j].first = std::sqrt(pow(scene->getNode(i)->x() - scene->getNode(j)->x(), 2) + pow(scene->getNode(i)->y() - scene->getNode(j)->y(), 2));
            }
        }
    }
    MatrixD matrix(m, table, table);
    matrix.set_bottomLimit(matrix.sum_of_const());
    commivoyager(matrix);

    textEdit->clear();
    textEdit->insertPlainText("Путь:\n");
    for(int i = 0; i < total_path.size(); i++){
        scene->addEdge(scene->getNode(total_path[i].first)->x(), scene->getNode(total_path[i].first)->y(),
                       scene->getNode(total_path[i].second)->x(), scene->getNode(total_path[i].second)->y());
        if(i == total_path.size()-1){
            textEdit->insertPlainText(QString::number(scene->getNodeId(total_path[i].first)) + "->" + QString::number(scene->getNodeId(total_path[i].second)));
        } else{
            textEdit->insertPlainText(QString::number(scene->getNodeId(total_path[i].first)) + "->");
        }
    }
    textEdit->insertPlainText("\nДлина пути(в пикселях): " + QString::number(record));
}


void Method::clearButtont_clicked(){
    textEdit->clear();
    textEdit->append("ПКМ - создать вершину");
    textEdit->append("ПКМ по вершине - удалить вершину");
    textEdit->append("ЛКМ по вершине + вести - переместить вершину");
    scene->deleteEdges();
    record = std::numeric_limits<int>::max();
    total_path.clear();
    view->setEnabled(true);
}

void Method::againButtont_clicked(){
    clearButtont_clicked();
    scene->deleteNodes();
    Node::id = 1;
}
