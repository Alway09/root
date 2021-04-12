#include "mnk.h"
#include "ui_mnk.h"
#include<QVector>

MNK::MNK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MNK)
{
    ui->setupUi(this);
}

MNK::~MNK()
{
    delete ui;
}

float func(double k, double x, double b){
    return k*x+b;
}

void MNK::on_pushButtonM_clicked()
{
    int N = 10;  // кол-во исходных точек
    int n = 0;  // кло-во точек на графике
    double h = 0.01; // шаг
    double ax = 0, bx = 10;
    QVector<double> x(N);//double *x = new double[N];
    QVector<double> y(N);//double *y = new double[N];

    double *summs = new double[4];
    for(int i = 0; i < 4; i++){
        summs[i] = 0;
    }

    x[0] = 4.7; y[0] = 2.8; // точки
    x[1] = 4.8; y[1] = 3.5;
    x[2] = 5.3; y[2] = 4.3;
    x[3] = 5.6; y[3] = 4.1;
    x[4] = 5.9; y[4] = 5.4;
    x[5] = 6.7; y[5] = 6.3;
    x[6] = 7.2; y[6] = 6.9;
    x[7] = 7.7; y[7] = 7.9;
    x[8] = 8.0; y[8] = 8.1;
    x[9] = 9.0; y[9] = 8.3;


    for(int i = 0; i < N; i++){
        summs[0] += x[i];
        summs[1] += y[i];
        summs[2] += x[i]*y[i];
        summs[3] += x[i]*x[i];
    }

    double k = (summs[2]-summs[0]*summs[1]/N)/(summs[3]-summs[0]*summs[0]/N);
    double b = (summs[1]-k*summs[0])/N;
    //--------------------------------------------------
    for(double i = ax; i < bx; i+=h){
        n++;
    }
    QVector<double> X(n); //double *X = new double[n];
    int c = 0;
    for(double i = ax; i < bx; i+=h){
        X[c] = i;
        c++;
    }
    QVector<double> Y(n); //double *Y = new double[n];
    for(int i = 0; i < n; i++){
        Y[i] = func(k, X[i], b);
    }
    //--------------------------------------------------

    double minX = X[0], maxX = X[0];
    double minY = Y[0], maxY = Y[0];
    for(int i = 1; i < n; i++){ // вычисление границ графика
        if(X[i] > maxX) maxX = X[i];
        if(X[i] < minX) minX = X[i];
        if(Y[i] > maxY) maxY = Y[i];
        if(Y[i] < minY) minY = Y[i];
    }

    ui->labelK->setNum(k);
    ui->labelB->setNum(b);

    ui->labelX1->setNum(x[0]);
    ui->labelX2->setNum(x[1]);
    ui->labelX3->setNum(x[2]);
    ui->labelX4->setNum(x[3]);
    ui->labelX5->setNum(x[4]);
    ui->labelX6->setNum(x[5]);
    ui->labelX7->setNum(x[6]);
    ui->labelX8->setNum(x[7]);
    ui->labelX9->setNum(x[8]);
    ui->labelX10->setNum(x[9]);
    ui->labelY1->setNum(y[0]);
    ui->labelY2->setNum(y[1]);
    ui->labelY3->setNum(y[2]);
    ui->labelY4->setNum(y[3]);
    ui->labelY5->setNum(y[4]);
    ui->labelY6->setNum(y[5]);
    ui->labelY7->setNum(y[6]);
    ui->labelY8->setNum(y[7]);
    ui->labelY9->setNum(y[8]);
    ui->labelY10->setNum(y[9]);

    ui->widgetM->clearGraphs();
    ui->widgetM->addGraph();
    ui->widgetM->graph(0)->setData(X, Y);
    ui->widgetM->xAxis->setLabel("x");
    ui->widgetM->yAxis->setLabel("y");
    ui->widgetM->xAxis->setRange(minX, maxX);
    ui->widgetM->yAxis->setRange(minY, maxY);

    ui->widgetM->addGraph();
    ui->widgetM->graph(1)->setData(x, y);
    ui->widgetM->graph(1)->setPen(QColor(50,50,50,255));
    ui->widgetM->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widgetM->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui->widgetM->replot();

}

void MNK::on_pushButton_clicked()
{

}
