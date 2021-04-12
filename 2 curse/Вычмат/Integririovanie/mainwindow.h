#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void setInfoL(double h, double result, double e, QString method);
    void leftRectLine(double e, double a, double b);
    void rightRectLine(double e, double a, double b);
    void midRectLine(double e, double a, double b);
    void trapLine(double e, double a, double b);
    void polyLine(double e, double a, double b);
    void setInfoS(double h, double result, double e, QString method);
    void leftRectSq(double e, double a, double b);
    void rightRectSq(double e, double a, double b);
    void midRectSq(double e, double a, double b);
    void trapSq(double e, double a, double b);
    void polySq(double e, double a, double b);
    void setInfoV(double h, double result, double e, QString method);
    void leftRectSin(double e, double a, double b);
    void rightRectSin(double e, double a, double b);
    void midRectSin(double e, double a, double b);
    void trapSin(double e, double a, double b);
    void polySin(double e, double a, double b);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
