#include "newton.h"
#include "ui_newton.h"
#include<fstream>

Newton::Newton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newton)
{
    ui->setupUi(this);
}

Newton::~Newton()
{
    delete ui;
}

double f(double x){
    return (2.0*cos(5.0*x)/3.0)-(x/6.0)+(1.0/3.0);
}

void Newton::on_pushButton_2_clicked()
{
    int a = -5, b = 5, N = 0; // a, b - границы интерполирования
    double h = 0.5;// шаг
    for(double i = a; i <= b; i += h){
        N++;
    }
    std::ofstream file("/home/alway/newton.txt");
    file << N << "\n";
    for(double i = a; i <= b; i += h){
        file << i << " " << f(i) << "\n";
    }
    file.close();
}

double newton(QVector<double> x, QVector<double> y, double X){
    QVector<double> temp(y.size());
    QVector<double> temp1(y.size());
    for(int i = 0; i < temp1. size(); i++){
        temp1[i] = 1;
    }
    temp = y;
    double result = temp[0];
    int inter = 0;
    int c = x.size()-1;
    int count = 1;

    for(int i = 1; i < y.size(); i++){
        for(int j = 0; j < c; j++){
            temp[j] = (temp[j+1]-temp[j])/(x[j+1+inter] - x[j]);
        }
        inter++;
        c--;
        for(int j = 0; j < count; j++){
            temp1[i] *= (X-x[j]);
        }
        count++;
        temp1[i] *= temp[0];
        result += temp1[i];

    }

    return result;
}

void Newton::on_pushButton_clicked()
{
    int N; int n = 0;
    double h = 0.01;

    std::ifstream file("/home/alway/newton.txt");
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
        Y[i] = newton(x, y, X[i]);
        Y1[i] = f(X[i]);
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
    double control1 = newton(x, y, xc);
    double control2 = f(xc);
    ui->labelY1->setNum(control1);
    ui->labelY2->setNum(control2);
    ui->label_9->setNum(xc);

    ui->widgetN->clearGraphs();
    ui->widgetN->addGraph();
    ui->widgetN->graph(0)->setData(X, Y);
    ui->widgetN->xAxis->setLabel("x");
    ui->widgetN->yAxis->setLabel("y");
    ui->widgetN->xAxis->setRange(minX-1, maxX+1);
    ui->widgetN->yAxis->setRange(minY1-1, maxY1+1);

    ui->widgetN->addGraph();
    ui->widgetN->graph(1)->setData(x, y);
    ui->widgetN->graph(1)->setPen(QColor(50,50,50,255));
    ui->widgetN->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widgetN->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));

    ui->widgetN->addGraph();
    ui->widgetN->graph(2)->setData(X, Y1);
    ui->widgetN->graph(2)->setPen(QColor(125, 100, 75, 255));

    ui->widgetN->replot();
}

void Newton::on_pushButton_4_clicked()
{
    double buf1, buf2;
    int N;
    std::ofstream file("/home/alway/newton.txt");
    std::ifstream primer("/home/alway/primer1.txt");
    primer >> N; file << N;

    for(int i = 0; i < N; i++){
        primer >> buf1 >> buf2;
        file << buf1 << " " << buf2 << "\n";
    }
    file.close();
    primer.close();
}

void Newton::on_pushButton_5_clicked()
{
    double buf1, buf2;
    int N;
    std::ofstream file("/home/alway/newton.txt");
    std::ifstream primer("/home/alway/primer2.txt");
    primer >> N; file << N;

    for(int i = 0; i < N; i++){
        primer >> buf1 >> buf2;
        file << buf1 << " " << buf2 << "\n";
    }
    file.close();
    primer.close();
}
