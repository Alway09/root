#include "interpolation.h"
#include "ui_interpolation.h"
#include <QVector>
#include<iostream>
#include<fstream>

Interpolation::Interpolation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Interpolation)
{
    ui->setupUi(this);
}

Interpolation::~Interpolation()
{
    delete ui;
}

double lagrange(QVector<double> x, QVector<double> y, double X){
    double result = 0;
    double p;
    for(int i = 0; i < x.size(); i++){
        p = 1;
        for(int j = 0; j < x.size(); j++){
            if(j!=i){
                p *= (X-x[j])/(x[i]-x[j]);
            }
        }
        result += y[i]*p;
    }

    return result;
}

double func(double x){
    return (2.0*cos(5.0*x)/3.0)-(x/6.0)+(1.0/3.0);
}

void Interpolation::on_pushButton_clicked()
{
    int N; int n = 0;
    double h = 0.01;

    std::ifstream file("/home/alway/lagrange.txt");
    file >> N;
    QVector<double> x(N);
    QVector<double> y(N);

    for(int i = 0; i < N; i++){
        file >> x[i] >> y[i];
    }
    file.close();

    for(double i = x[0]; i < x[N-1]; i+=h){
        n++;
    }
    QVector<double> X(n);
    int c = 0;
    for(double i = x[0]; i < x[N-1]; i+=h){
        X[c] = i;
        c++;
    }
    QVector<double> Y(n);
    QVector<double> Y1(n);
    for(int i = 0; i < n; i++){
        Y[i] = lagrange(x, y, X[i]);
        Y1[i] = func(X[i]);
    }

    double minX = X[0], maxX = X[0];
    double minY1 = Y1[0], maxY1 = Y1[0];
    double minY = Y[0], maxY = Y[0];
    for(int i = 1; i < n; i++){ // вычисление границ графика
        if(X[i] > maxX) maxX = X[i];
        if(X[i] < minX) minX = X[i];
        if(Y1[i] > maxY1) maxY1 = Y1[i];
        if(Y1[i] < minY1) minY1 = Y1[i];
        if(Y[i] > maxY) maxY = Y[i];
        if(Y[i] < minY) minY = Y[i];
    }

    ui->labelT->setNum(N);
    ui->labelS->setNum(x[1]-x[0]);
    double xc = x[9]+(x[1]-x[0])/2;
    double control1 = lagrange(x, y, xc);
    double control2 = func(xc);
    ui->label_8->setNum(xc);
    ui->label_9->setNum(control1);
    ui->label_10->setNum(control2);

    ui->widgetI->clearGraphs();
    ui->widgetI->addGraph();
    ui->widgetI->graph(0)->setData(X, Y);
    ui->widgetI->xAxis->setLabel("x");
    ui->widgetI->yAxis->setLabel("y");
    ui->widgetI->xAxis->setRange(minX-1, maxX+1);
    ui->widgetI->yAxis->setRange(minY1-1, maxY1+1);

    ui->widgetI->addGraph();
    ui->widgetI->graph(1)->setData(x, y);
    ui->widgetI->graph(1)->setPen(QColor(50,50,50,255));
    ui->widgetI->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widgetI->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));

    ui->widgetI->addGraph();
    ui->widgetI->graph(2)->setData(X, Y1);
    ui->widgetI->graph(2)->setPen(QColor(125, 100, 75, 255));

    ui->widgetI->replot();

}

void Interpolation::on_generateButton_clicked()
{
    int a = -5, b = 5, N = 0; // a, b - границы интерполирования
    double h = 0.5;// шаг
    for(double i = a; i <= b; i += h){
        N++;
    }
    std::ofstream file("/home/alway/lagrange.txt");
    file << N << "\n";
    for(double i = a; i <= b; i += h){
        file << i << " " << func(i) << "\n";
    }
    file.close();
}

void Interpolation::on_pushButton_3_clicked()
{
    double buf1, buf2;
    int N;
    std::ofstream file("/home/alway/lagrange.txt");
    std::ifstream primer("/home/alway/primer1.txt");
    primer >> N; file << N;

    for(int i = 0; i < N; i++){
        primer >> buf1 >> buf2;
        file << buf1 << " " << buf2 << "\n";
    }
    file.close();
    primer.close();
}

void Interpolation::on_pushButton_4_clicked()
{
    double buf1, buf2;
    int N;
    std::ofstream file("/home/alway/lagrange.txt");
    std::ifstream primer("/home/alway/primer2.txt");
    primer >> N; file << N;

    for(int i = 0; i < N; i++){
        primer >> buf1 >> buf2;
        file << buf1 << " " << buf2 << "\n";
    }
    file.close();
    primer.close();
}
