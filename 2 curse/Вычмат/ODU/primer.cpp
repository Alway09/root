#include "primer.h"
#include "ui_primer.h"
#include<cmath>

Primer::Primer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Primer)
{
    ui->setupUi(this);
}

Primer::~Primer()
{
    delete ui;
}

double referenceF2(double x){
    return exp(-1*x);
}
double referenceF1(double x){
    return exp(x);
}
double referenceF(double x){
    return sqrt(x*x+16);
}

double f1(double t, double y_2){
    return exp(2*t)*y_2;
}
double f2(double t, double y_1){
    return -exp(-2*t)*y_1;
}

double f(double x, double y){
    return x/y;
}

double rk1(double y_n1, double y_n2, double t_n, double h){
    double k_1 = f1(t_n, y_n2);
    double k_2 = f1(t_n + h/2, y_n2 + h/2*k_1);
    double k_3 = f1(t_n+h, y_n2 - h*k_1 + h*2*k_2);
    return y_n1 + h*(k_1 + 4*k_2 + k_3)/6;
}

double rk2(double y_n1, double y_n2, double t_n, double h){
    double k_1 = f2(t_n, y_n1);
    double k_2 = f2(t_n + h/2, y_n1 + h/2*k_1);
    double k_3 = f2(t_n+h, y_n1 - h*k_1 + h*2*k_2);
    return y_n2 + h*(k_1 + 4*k_2 + k_3)/6;
}

double rk(double y, double x, double h){
    double k_1 = f(x, y);
    double k_2 = f(x+h/2, y+h/2*k_1);
    double k_3 = f(x+h, y-h*k_1+2*h*k_2);
    return y+h*(k_1+4*k_2+k_3)/6;
}
void Primer::on_pushButton_clicked()
{
    double a = 0, b = 4, h = 0.00001;
    int N = 0;
    for(double i = a; i <= b; i+= h){
        N++;
    }
    QVector<double> x(N);
    QVector<double> y(N);
    QVector<double> y1(N);
    QVector<double> y2(N);
    QVector<double> y_r(N);
    QVector<double> y_r1(N);
    QVector<double> y_r2(N);
    N = 0;
    for(double i = a; i <= b; i+= h){
        x[N] = i;
        y_r[N] = referenceF(i);
        y_r1[N] = referenceF1(i);
        y_r2[N] = referenceF2(i);
        N++;
    }
    y[0] = 4;
    y1[0] = referenceF1(0);
    y2[0] = referenceF2(0);
    for(int i = 1; i < N; i++){
        y[i] = rk(y[i-1], x[i-1], h);
        y1[i] = rk1(y1[i-1], y2[i-1], x[i-1], h);
        y2[i] = rk2(y1[i-1], y2[i-1], x[i-1], h);
    }

    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->xAxis->setRange(0, 4);
    ui->widget->yAxis->setRange(0, 80);
    ui->widget->graph(0)->setData(x, y1);
    ui->widget->graph(0)->setPen(QColor(50,50,50,255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x, y_r1);

    ui->widget->replot();
}
