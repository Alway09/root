#include "zadacha.h"
#include "ui_zadacha.h"
#include"qcustomplot.h"
#include<functional>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<cmath>
#include<QGroupBox>
#include<algorithm>
#include<QLabel>
#include<QLineEdit>
#include<cstdlib>

using func_t = std::function<double(int, double, QVector<double>)>;
static double g_t_s{20};

Zadacha::Zadacha(QWidget *parent, bool flag) :
    QDialog(parent),
    ui(new Ui::Zadacha)
{
    ui->setupUi(this);

    if(flag){
        this->setMinimumWidth(900);
        this->setMinimumHeight(900);

        QVBoxLayout* mainLay = new QVBoxLayout(this);
        QVBoxLayout* box1Lay = new QVBoxLayout;
        QVBoxLayout* box2Lay = new QVBoxLayout;
        QHBoxLayout* gr_err = new QHBoxLayout;
        QHBoxLayout* box11Lay = new QHBoxLayout;
        QHBoxLayout* box12Lay = new QHBoxLayout;
        QHBoxLayout* under = new QHBoxLayout;

        QPushButton* testB = new QPushButton("Построить график");
        connect(testB, SIGNAL(clicked()), this, SLOT(testButton_clicked()));

        QGroupBox* box1 = new QGroupBox("Результат работы программы(точки) и точное решение(линии)");
        QCustomPlot* graph = new QCustomPlot;
        graph->xAxis->setLabel("t");
        graph->yAxis->setLabel("u(t)");
        graphics = graph;
        box1Lay->addWidget(graph);

        QGroupBox* box11 = new QGroupBox("Границы");
        box11->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QHBoxLayout* borders = new QHBoxLayout;
        QLabel* l1 = new QLabel("a:");
        QLabel* l2 = new QLabel("b:");
        QLineEdit* first = new QLineEdit("0");
        start_p = first;
        QLineEdit* second = new QLineEdit("2");
        finish_p = second;
        borders->addWidget(l1);
        borders->addWidget(first);
        borders->addWidget(l2);
        borders->addWidget(second);
        box11Lay->addLayout(borders);
        box11->setLayout(box11Lay);

        QGroupBox* box12 = new QGroupBox("Шаг");
        box12->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QLabel* l3 = new QLabel("h");
        QLineEdit* stp = new QLineEdit("0.02");
        step = stp;
        box12Lay->addWidget(l3);
        box12Lay->addWidget(stp);
        box12->setLayout(box12Lay);

        under->addWidget(box11);
        under->addWidget(box12);
        box1Lay->addLayout(under);
        box1Lay->addWidget(testB);
        box1->setLayout(box1Lay);

        QGroupBox* box2 = new QGroupBox("Графики зависимостимаксимальной погрешности решения e и e/h^2 от выбранного шага h");
        QPushButton* errorsB = new QPushButton("Построить графики");
        connect(errorsB, SIGNAL(clicked()), this, SLOT(errorsButton_clicked()));
        QCustomPlot* grErr1 = new QCustomPlot;
        grErr1->xAxis->setLabel("h");
        grErr1->yAxis->setLabel("e");
        QCustomPlot* grErr2 = new QCustomPlot;
        grErr2->xAxis->setLabel("h");
        grErr2->yAxis->setLabel("e/h^2");
        maxErr1 = grErr1;
        maxErr2 = grErr2;
        gr_err->addWidget(grErr1);
        gr_err->addWidget(grErr2);
        box2Lay->addLayout(gr_err);
        box2Lay->addWidget(errorsB);
        box2->setLayout(box2Lay);

        mainLay->addWidget(box1);
        mainLay->addWidget(box2);
        mainLayout = mainLay;
        setLayout(mainLay);
    } else{
        this->setMinimumWidth(1000);
        this->setMinimumHeight(400);

        QHBoxLayout* mainLay = new QHBoxLayout(this);
        QVBoxLayout* boxGr1 = new QVBoxLayout;
        QVBoxLayout* boxGr2 = new QVBoxLayout;
        QHBoxLayout* box2Lay = new QHBoxLayout;
        QHBoxLayout* under1 = new QHBoxLayout;
        QHBoxLayout* under2 = new QHBoxLayout;

        QPushButton* osnB1 = new QPushButton("Построить график");
        connect(osnB1, SIGNAL(clicked()), this, SLOT(osnButton1_clicked()));

        QGroupBox* box2 = new QGroupBox("Шаг");
        box2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QLabel* l3 = new QLabel("h");
        QLineEdit* stp = new QLineEdit("0.02");
        step = stp;
        box2Lay->addWidget(l3);
        box2Lay->addWidget(stp);
        box2->setLayout(box2Lay);

        //under1->addWidget(box1);
        under1->addWidget(box2);

        QCustomPlot* graph = new QCustomPlot;
        graph->xAxis->setLabel("t");
        graph->yAxis->setLabel("z");
        graphics = graph;

        QVBoxLayout* maximum1 = new QVBoxLayout;
        QGroupBox* boxMaxZ1 = new QGroupBox("Максимальная высота");
        boxMaxZ1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QLabel* l5 = new QLabel("0");
        l5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        max_z1 = l5;
        maximum1->addWidget(l5);
        boxMaxZ1->setLayout(maximum1);
        under1->addWidget(boxMaxZ1);

        boxGr1->addWidget(graph);
        boxGr1->addLayout(under1);
        boxGr1->addWidget(osnB1);

        QGroupBox* gr1 = new QGroupBox("Зависимость высоты полета от времени");
        gr1->setLayout(boxGr1);

        QCustomPlot* graph2 = new QCustomPlot;
        maximum_z = graph2;
        graph2->xAxis->setLabel("t");
        graph2->yAxis->setLabel("z");

        QPushButton* osnB2 = new QPushButton("Рассчитать");
        connect(osnB2, SIGNAL(clicked()), this, SLOT(osnButton2_clicked()));

        QGroupBox* gr2 = new QGroupBox("Максимальная высота подъема");
        gr2->setLayout(boxGr2);

        QGroupBox* optimal = new QGroupBox("Оптимальное время выгорания топлива");
        optimal->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QVBoxLayout* opt = new QVBoxLayout;
        QLabel* opt_l = new QLabel("0");
        optimal_t_s = opt_l;
        opt->addWidget(opt_l);
        optimal->setLayout(opt);

        QGroupBox* boxMaxZ2 = new QGroupBox("Максимальная высота");
        boxMaxZ2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QVBoxLayout* maxZ2Lay = new QVBoxLayout;
        QLabel* maxZ2 = new QLabel("0");
        max_z2 = maxZ2;
        maxZ2Lay->addWidget(maxZ2);
        boxMaxZ2->setLayout(maxZ2Lay);

        under2->addWidget(optimal);
        under2->addWidget(boxMaxZ2);

        boxGr2->addWidget(graph2);
        boxGr2->addLayout(under2);
        boxGr2->addWidget(osnB2);

        mainLay->addWidget(gr1);
        mainLay->addWidget(gr2);
        setLayout(mainLay);
    }
}

Zadacha::~Zadacha()
{
    delete ui;
}

double primer_f2(int id, double t, QVector<double> y){
    using namespace std;
    switch (id){
    case 0:
        return -1*sin(t)/pow(1+exp(2*t), 0.5) + y[0]*(pow(y[0], 2) + pow(y[1], 2) -1);
        break;
    case 1:
        return cos(t)/pow(1+exp(2*t), 0.5) + y[1]*(pow(y[0],2) + pow(y[1],2) -1 );
        break;
    default:
        return 0;
        break;
    }
}

QVector<double> solution_f2(int id, QVector<double> t){
    using namespace std;
    QVector<double> ans;
    switch(id){
    case 0:
        for(int i = 0; i < t.size(); i++){
            ans.push_back(cos(t[i])/pow(1+exp(2*t[i]), 0.5));
        }
        break;
    case 1:
        for(int i = 0; i < t.size(); i++){
            ans.push_back(sin(t[i])/pow(1+exp(2*t[i]), 0.5));
        }
        break;
    default:
        break;
    }
    return ans;
}

double primer_f3(int id, double t, QVector<double> y){
    using namespace std;
    double b_1{1};
    double b_2{3};
    double c{3};
    double l_1{1};
    double l_2{1};
    switch(id){
    case 0:
        return (-1*l_1 + b_1*pow(y[1], 2.0/3.0)*(1-y[0]/c)/(1+y[0])) * y[0];
        break;
    case 1:
        return l_2*y[1] - b_2*y[0]*pow(y[1], 2.0/3.0)/(1+y[0]);
        break;
    default:
        return 0;
        break;
    }
}

double primer_f(int id, double t, QVector<double> y){
    using namespace std;
    switch (id){
    case 0:
        return y[0]/(2+2*t) - 2*t*y[1];
        break;
    case 1:
        return y[1]/(2+2*t) + 2*t*y[0];
        break;
    default:
        return 0;
        break;
    }
}

QVector<double> solution_f(int id, QVector<double> t){
    using namespace std;
    QVector<double> ans;
    switch(id){
    case 0:
        for(int i = 0; i < t.size(); i++){
            ans.push_back(cos(t[i]*t[i])*sqrt(1+t[i]));
        }
        break;
    case 1:
        for(int i = 0; i < t.size(); i++){
            ans.push_back(sin(t[i]*t[i])*sqrt(1+t[i]));
        }
        break;
    default:
        break;
    }
    return ans;
}

double osn_f(int id, double t, QVector<double> y){
    double g{0.01};
    double alpha{2};
    double c{0.05};
    double gamma{0.01};
    double m_t{0.8};
    double q;
    if(t <= g_t_s){
        q = m_t/g_t_s;
    } else{
        q = 0;
    }

    switch(id){
    case 0:
        return -1*q;
        break;
    case 1:
        return y[2];
        break;
    case 2:
        return -1*g + (1/y[0])*(alpha*q - c*exp(-1*gamma*y[1]*y[1])*y[2]*y[2]);
        break;
    default:
        return 0;
        break;
    }
}

QVector<double> addToElem(double d, QVector<double> v){
    for(int i = 0; i < v.size(); ++i){
        v[i] += d;
    }
    return v;
}

QVector<QVector<double>> runge_kutt(func_t f, QVector<QVector<double>> y, QVector<double> t, double h){  //в у содержатся стартовые значения
    //QVector<QPair<double, double>> ur1, ur2;
    for(int i = 0; i < t.size()-1; ++i){
        y.push_back(QVector<double>());
        for(int j = 0; j < y[i].size(); ++j){
            double k_1 = f(j, t[i], y[i]);
            double k_2 = f(j, t[i] + (h/2), addToElem(((h/2)*k_1), y[i]));
            /*if(j == 0){
                ur1.push_back({k_1, k_2});
            }else if(j ==1){
                ur2.push_back({k_1, k_2});
            }*/
            y[i+1].push_back(y[i][j] + h*(k_1 + k_2)/2);
        }
    }

    QVector<QVector<double>> transp(y[0].size(), QVector<double>(y.size()));
    for(int i = 0; i < y.size(); ++i){
        for(int j = 0; j < y[i].size(); ++j){
            transp[j][i] = y[i][j];
        }
    }
    return transp;
}

void show_graphs(QVector<double> t, QVector<QVector<double>> dots, QVector<QVector<double>> solution, QCustomPlot* p){
    int k{0};
    std::srand(3213);
    QVector<QColor> colors;
    for(int i = 0; i < dots.size(); i++){
        p->addGraph();
        p->graph(i)->setData(t, dots[i]);
        p->graph(i)->setLineStyle(QCPGraph::lsNone);
        colors.push_back(QColor(std::rand()%255, std::rand()%255, std::rand()%255));
        p->graph(i)->setPen(colors.last());
        p->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
        k++;
    }
    for(int j = 0; j < solution.size(); j++){
        p->addGraph();
        p->graph(k)->setData(t, solution[j]);
        p->graph(k)->setPen(colors[j]);
        k++;
    }
    p->xAxis->setRange(0, t.last());
    p->yAxis->setRange(-10, 10);
    p->replot();
}

void Zadacha::max_errors(func_t f, std::function<QVector<double>(int, QVector<double>)> solution_f, double a, double b, int n){// n - кол-во уравнений
    QVector<double> ans1, ans2, h_v;
    double h = 0.09;
    while(h > 0.0001){
        QVector<double> t;
        for(double i = a; i <= b; i+=h){
            t.push_back(i);
        }

        QVector<QVector<double>> solution;
        for(int i = 0; i < n; ++i){
            solution.push_back(solution_f(i, t));
        }

        QVector<QVector<double>> y; y.push_back(QVector<double>());
        for(int i = 0; i < solution.size(); i++){
            y[0].push_back(solution[i][0]);
        }

        auto dots{runge_kutt(f, y, t, h)};
        QVector<double> norms;

        for(int i = 0; i < dots[0].size(); ++i){
            for(int j = 0; j < dots.size(); ++j){
                norms.push_back(std::abs(solution[j][i]-dots[j][i]));
            }
        }
        ans1.push_back(*std::max_element(norms.begin(), norms.end()));
        h_v.push_back(h);
        ans2.push_back(ans1.last()/(h*h));
        h /= 1.2;
    }

    maxErr1->addGraph();
    maxErr1->yAxis->setRange(0, *std::max_element(ans1.begin(), ans1.end()));
    maxErr1->graph(0)->setData(h_v, ans1);
    maxErr1->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    maxErr1->xAxis->setRange(0, h_v[0]);

    maxErr2->addGraph();
    maxErr2->graph(0)->setData(h_v, ans2);
    maxErr2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    maxErr2->xAxis->setRange(0, h_v[0]);
    maxErr2->yAxis->setRange(0, 13500);

    maxErr1->replot();
    maxErr2->replot();
}

void Zadacha::testButton_clicked(){
    double a{start_p->text().toDouble()}, b{finish_p->text().toDouble()}, h{step->text().toDouble()};
    int n{2};

    QVector<double> t;
    for(double i = a; i <= b; i+=h){
        t.push_back(i);
    }

    QVector<QVector<double>> solution;
    for(int i = 0; i < n; ++i){
        solution.push_back(solution_f(i, t));
    }

    QVector<QVector<double>> y; y.push_back(QVector<double>());
    for(int i = 0; i < solution.size(); i++){
        y[0].push_back(solution[i][0]);
    }

    show_graphs(t, runge_kutt(primer_f, y, t, h), solution, graphics);
}

void Zadacha::errorsButton_clicked(){
    double a{start_p->text().toDouble()}, b{finish_p->text().toDouble()};
    int n{2};
    max_errors(primer_f, solution_f, a, b, n);
}

void Zadacha::osnButton1_clicked(){
    double a{0}, b{100}, h{step->text().toDouble()};
    double m_0{1}, z_0{0}, v_0{0};

    QVector<double> t;
    for(double i = a; i <= b; i+=h){
        t.push_back(i);
    }
    QVector<QVector<double>> y; y.push_back(QVector<double>());
    y[0].push_back(m_0);
    y[0].push_back(z_0);
    y[0].push_back(v_0);

    auto ans = runge_kutt(osn_f, y, t, h);
    max_z1->setText(QString::number(*std::max_element(ans[1].begin(), ans[1].end())));
    graphics->addGraph();
    graphics->graph(0)->setData(t, ans[1]);
    graphics->xAxis->setRange(a, b);
    graphics->yAxis->setRange(0, max_z1->text().toDouble());
    graphics->replot();
}

void Zadacha::osnButton2_clicked(){
    /*double a{0}, b{100}, h{0.001};
    double m_0{1}, z_0{0}, v_0{0};

    QVector<double> t;
    for(double i = a; i <= b; i+=h){
        t.push_back(i);
    }
    QVector<QVector<double>> y; y.push_back(QVector<double>());
    y[0].push_back(m_0);
    y[0].push_back(z_0);
    y[0].push_back(v_0);

    double m_z = std::numeric_limits<double>::min();
    double mem_t{0};
    for(double i = 3; i <= 30; ++i){
        g_t_s = i;
        auto ans = runge_kutt(osn_f, y, t, h);
        double tmp = *std::max_element(ans[1].begin(), ans[1].end());
        if(tmp > m_z){
            m_z = tmp;
            mem_t = i;
        }
    }

    g_t_s = mem_t;
    auto fin = runge_kutt(osn_f, y, t, h);

    max_z2->setText(QString::number(*std::max_element(fin[1].begin(), fin[1].end())));

    maximum_z->addGraph();
    maximum_z->graph(0)->setData(t, fin[1]);
    maximum_z->yAxis->setRange(0, max_z2->text().toDouble());
    maximum_z->xAxis->setRange(a, b);
    maximum_z->replot();

    optimal_t_s->setText((QString::number(g_t_s)));

    g_t_s = 20;*/
    double a{0}, b{20}, h{0.001};

    QVector<double> t;
    for(double i = a; i <= b; i+=h){
        t.push_back(i);
    }

    QVector<QVector<double>> y; y.push_back(QVector<double>());
    y[0].push_back(1);
    y[0].push_back(1);

    auto result{runge_kutt(primer_f3, y, t, h)};

    maximum_z->addGraph();
    maximum_z->graph(0)->setData(result[0], result[1]);
    //maximum_z->xAxis->setRange(*std::min_element(result[0].begin(), result[0].end()), *std::max_element(result[0].begin(), result[0].end()));
    maximum_z->xAxis->setRange(a, b);
    maximum_z->yAxis->setRange(*std::min_element(result[1].begin(), result[1].end()), *std::max_element(result[1].begin(), result[1].end()));
    maximum_z->replot();
}
