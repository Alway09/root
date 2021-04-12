#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<cmath>
#include<QMessageBox>
#include<iostream>
#include<QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------
double lineF(double x){
    return 3.4*x-1;
}

double squareF(double x){
    return 3*x*x-3;
}

double sinF(double x){
    return (2.0*cos(5.0*x)/3.0)-(x/6.0)+(1.0/3.0);
}

void MainWindow::setInfoL(double h, double result, double e, QString method){
    QString str;
    ui->textLine->setFontItalic(true);
    ui->textLine->setTextColor(Qt::GlobalColor::darkRed);
    ui->textLine->append(method);
    ui->textLine->setTextColor(Qt::GlobalColor::black);
    ui->textLine->setFontItalic(false);
    ui->textLine->append("Результат: " + str.setNum(result));
    ui->textLine->append("Шаг:" + str.setNum(h));
    ui->textLine->append("Погрешность: " + str.setNum(e));
}

void MainWindow::setInfoS(double h, double result, double e, QString method){
    QString str;
    ui->textSq->setFontItalic(true);
    ui->textSq->setTextColor(Qt::GlobalColor::darkRed);
    ui->textSq->append(method);
    ui->textSq->setTextColor(Qt::GlobalColor::black);
    ui->textSq->setFontItalic(false);
    ui->textSq->append("Результат: " + str.setNum(result));
    ui->textSq->append("Шаг:" + str.setNum(h));
    ui->textSq->append("Погрешность: " + str.setNum(e));
}

void MainWindow::setInfoV(double h, double result, double e, QString method){
    QString str;
    ui->textVar->setFontItalic(true);
    ui->textVar->setTextColor(Qt::GlobalColor::darkRed);
    ui->textVar->append(method);
    ui->textVar->setTextColor(Qt::GlobalColor::black);
    ui->textVar->setFontItalic(false);
    ui->textVar->append("Результат: " + str.setNum(result));
    ui->textVar->append("Шаг:" + str.setNum(h));
    ui->textVar->append("Погрешность: " + str.setNum(e));
}
//----------------------------------------------------------------------------
double tempLeftRectLine(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(lineF(a+i*h));
    }
    return result;
}

void MainWindow::leftRectLine(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод левых прямоугольников";

    while(e <= (abs(tempLeftRectLine(a,b,h)-tempLeftRectLine(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoL(h, tempLeftRectLine(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempRightRectLine(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N; i++){
        result += h*(lineF(a+i*h));
    }
    return result;
}

void MainWindow::rightRectLine(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод правых прямоугольников";

    while(e <= (abs(tempRightRectLine(a,b,h)-tempRightRectLine(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoL(h, tempRightRectLine(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempMidRectLine(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(lineF(a+(i+0.5)*h));
    }
    return result;
}

void MainWindow::midRectLine(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод средних прямоугольников";

    while(e <= (abs(tempMidRectLine(a,b,h)-tempMidRectLine(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoL(h, tempMidRectLine(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempTrapLine(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N-1; i++){
        result += lineF(a+i*h);
    }
    result += lineF(a)/2+lineF(b)/2;
    result *= h;

    return result;
}

void MainWindow::trapLine(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод трапеций";

    while(e <= (abs(tempTrapLine(a,b,h)-tempTrapLine(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoL(h, tempTrapLine(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempPolyLine(double a, double b, double h){
    int N = ceil((b-a)/h);
    double result = 0;
    double ch=0, nch=0;
    for(int i = 1; i <= N-1; i+=2){
        nch += lineF(a+i*h);
    }
    for(int i = 2; i <= N-2; i+=2){
        ch += lineF(a+i*h);
    }
    result = (h/3)*(lineF(a) + 4*nch + 2*ch + lineF(b));

    return result;
}

void MainWindow::polyLine(double e, double a, double b){
    int n = 2;
    QString method = "Метод Симпсона";

    while(e <= (abs(tempPolyLine(a,b,(b-a)/n)-tempPolyLine(a,b,((b-a)/n)/2))/(pow(2, 4)-1))){
        n *= 2;
    }

    setInfoL((b-a)/n, tempPolyLine(a,b,(b-a)/n), e, method);
}
//----------------------------------------------------------------------------
double tempLeftRectSq(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(squareF(a+i*h));
    }
    return result;
}

void MainWindow::leftRectSq(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод левых прямоугольников";

    while(e <= (abs(tempLeftRectSq(a,b,h)-tempLeftRectSq(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoS(h, tempLeftRectSq(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempRightRectSq(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N; i++){
        result += h*(squareF(a+i*h));
    }
    return result;
}

void MainWindow::rightRectSq(double e, double a, double b){
    double h = 1;
    QString method = "Метод правых прямоугольников";

    while(e <= (abs(tempRightRectSq(a,b,h)-tempRightRectSq(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoS(h, tempRightRectSq(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempMidRectSq(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(squareF(a+(i+0.5)*h));
    }
    return result;
}

void MainWindow::midRectSq(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод средних прямоугольников";

    while(e <= (abs(tempMidRectSq(a,b,h)-tempMidRectSq(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoS(h, tempMidRectSq(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempTrapSq(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N-1; i++){
        result += squareF(a+i*h);
    }
    result += squareF(a)/2+squareF(b)/2;
    result *= h;

    return result;
}

void MainWindow::trapSq(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод трапеций";

    while(e <= (abs(tempTrapSq(a,b,h)-tempTrapSq(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoS(h, tempTrapSq(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempPolySq(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    double ch=0, nch=0;
    for(int i = 1; i <= N-1; i+=2){
        nch += squareF(a+i*h);
    }
    for(int i = 2; i <= N-2; i+=2){
        ch += squareF(a+i*h);
    }
    result = (h/3)*(squareF(a) + 4*nch + 2*ch + squareF(b));

    return result;
}

void MainWindow::polySq(double e, double a, double b){
    int n = 2;
    QString method = "Метод Симпсона";

    while(e <= (abs(tempPolySq(a,b,(b-a)/n)-tempPolySq(a,b,((b-a)/n)/2))/(pow(2, 4)-1))){
        n *= 2;
    }

    setInfoS((b-a)/n, tempPolySq(a,b,(b-a)/n), e, method);
}
//----------------------------------------------------------------------------
double tempLeftRectSin(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(sinF(a+i*h));
    }
    return result;
}

void MainWindow::leftRectSin(double e, double a, double b){
    double h = 0.5;
    QString method = "Метод левых прямоугольников";

    while(e <= (abs(tempLeftRectSin(a,b,h)-tempLeftRectSin(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoV(h, tempLeftRectSin(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempRightRectSin(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N; i++){
        result += h*(sinF(a+i*h));
    }
    return result;
}

void MainWindow::rightRectSin(double e, double a, double b){
    double h = 0.5;
    QString method = "Метод правых прямоугольников";

    while(e <= (abs(tempRightRectSin(a,b,h)-tempRightRectSin(a,b,h/2))/(pow(2, 1)-1))){
        h /= 2;
    }

    setInfoV(h, tempRightRectSin(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempMidRectSin(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 0; i < N-1; i++){
        result += h*(sinF(a+(i+0.5)*h));
    }
    return result;
}

void MainWindow::midRectSin(double e, double a, double b){
    double h = 0.5;
    QString method = "Метод средних прямоугольников";

    while(e <= (abs(tempMidRectSin(a,b,h)-tempMidRectSin(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoV(h, tempMidRectSin(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempTrapSin(double a, double b, double h){
    int N = (b-a)/h;
    double result = 0;
    for(int i = 1; i < N-1; i++){
        result += sinF(a+i*h);
    }
    result += sinF(a)/2+sinF(b)/2;
    result *= h;

    return result;
}

void MainWindow::trapSin(double e, double a, double b){
    double h = (b-a);
    QString method = "Метод трапеций";

    while(e <= (abs(tempTrapSin(a,b,h)-tempTrapSin(a,b,h/2))/(pow(2, 2)-1))){
        h /= 2;
    }

    setInfoV(h, tempTrapSin(a,b,h), e, method);
}
//----------------------------------------------------------------------------
double tempPolySin(double a, double b, double h){
    int N = ceil((b-a)/h);
    double result = 0;
    double ch=0, nch=0;
    for(int i = 1; i <= N-1; i+=2){
        nch += sinF(a+i*h);
    }
    for(int i = 2; i <= N-2; i+=2){
        ch += sinF(a+i*h);
    }
    result = (h/3)*(sinF(a) + 4*nch + 2*ch + sinF(b));

    return result;
}

void MainWindow::polySin(double e, double a, double b){
    int n = 2;
    QString method = "Метод Симпсона";

    while(e <= (abs(tempPolySin(a,b,(b-a)/n)-tempPolySin(a,b,((b-a)/n)/2))/(pow(2, 4)-1))){
        n *= 2;
    }

    setInfoV((b-a)/n, tempPolySin(a,b,(b-a)/n), e, method);
}

int c = 1;
void MainWindow::on_pushButton_clicked()
{
    double e, gh = 0.01;
    int N = 0;
    QString str1, str2;
    e = ui->lineEdit->text().toDouble();
    if(e == 0){
        QMessageBox::critical(this, "Погрешность", "Погрешность равна нулю!");
        return;
    }

    ui->textLine->append(str1.setNum(c) + "------");
    double aL = ui->lineLA->text().toDouble();
    double bL = ui->lineLB->text().toDouble();
    ui->textLine->append("a = " + str1.setNum(aL) + " b = " + str2.setNum(bL));
    leftRectLine(e,aL,bL);
    rightRectLine(e, aL, bL);
    midRectLine(e, aL, bL);
    trapLine(e, aL, bL);
    polyLine(e, aL, bL);
    for(double i = aL; i < bL; i+=gh){
        N++;
    }
    QVector<double> xL(N);
    int count = 0;
    for(double i = aL; i < bL; i+=gh){
        xL[count] = i;
        count++;
    }
    QVector<double> yL(N);
    for(int i = 0; i < N; i++){
        yL[i] = lineF(xL[i]);
    }
    ui->widgetL->clearGraphs();
    ui->widgetL->addGraph();
    ui->widgetL->graph(0)->setData(xL, yL);
    ui->widgetL->xAxis->setRange(aL, bL);
    ui->widgetL->yAxis->setRange(lineF(aL), lineF(bL));
    ui->widgetL->replot();

    ui->textSq->append(str1.setNum(c) + "------");
    double aS = ui->lineSA->text().toDouble();
    double bS = ui->lineSB->text().toDouble();
    ui->textSq->append("a = " + str1.setNum(aS) + " b = " + str2.setNum(bS));
    leftRectSq(e, aS, bS);
    rightRectSq(e, aS, bS);
    midRectSq(e, aS, bS);
    trapSq(e, aS, bS);
    polySq(e, aS, bS);
    N = 0;
    for(double i = aS; i < bS; i+=gh){
        N++;
    }
    QVector<double> xS(N);
    count = 0;
    for(double i = aS; i < bS; i+=gh){
        xS[count] = i;
        count++;
    }
    QVector<double> yS(N);
    for(int i = 0; i < N; i++){
        yS[i] = squareF(xS[i]);
    }
    ui->widgetS->clearGraphs();
    ui->widgetS->addGraph();
    ui->widgetS->graph(0)->setData(xS, yS);
    ui->widgetS->xAxis->setRange(aS, bS);
    ui->widgetS->yAxis->setRange(squareF(aS), squareF(bS));
    ui->widgetS->replot();


    ui->textVar->append(str1.setNum(c) + "------");
    double aV = ui->lineVA->text().toDouble();
    double bV = ui->lineVB->text().toDouble();
    ui->textVar->append("a = " + str1.setNum(aV) + " b = " + str2.setNum(bV));
    leftRectSin(e, aV, bV);
    rightRectSin(e, aV, bV);
    midRectSin(e, aV, bV);
    trapSin(e, aV, bV);
    polySin(e, aV, bV);

    N = 0;
    for(double i = aV; i < bV; i+=gh){
        N++;
    }
    QVector<double> xV(N);
    count = 0;
    for(double i = aV; i < bV; i+=gh){
        xV[count] = i;
        count++;
    }
    QVector<double> yV(N);
    for(int i = 0; i < N; i++){
        yV[i] = sinF(xV[i]);
    }
    ui->widgetV->clearGraphs();
    ui->widgetV->addGraph();
    ui->widgetV->graph(0)->setData(xV, yV);
    ui->widgetV->xAxis->setRange(aV, bV);
    ui->widgetV->yAxis->setRange(-2, 2);
    ui->widgetV->replot();

    c++;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textVar->clear();
    ui->textSq->clear();
    ui->textLine->clear();
    c = 1;
}
