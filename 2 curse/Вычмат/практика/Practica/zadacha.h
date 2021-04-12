#ifndef ZADACHA_H
#define ZADACHA_H

#include <QDialog>
#include<QVBoxLayout>
#include<functional>
#include"qcustomplot.h"

using func_t = std::function<double(int, double, QVector<double>)>;

namespace Ui {
class Zadacha;
}

class Zadacha : public QDialog
{
    Q_OBJECT

public:
    explicit Zadacha(QWidget *parent = nullptr, bool flag = true);
    ~Zadacha();
    void max_errors(func_t, std::function<QVector<double>(int, QVector<double>)>, double, double, int);

private slots:
    void testButton_clicked();
    void errorsButton_clicked();
    void osnButton1_clicked();
    void osnButton2_clicked();

private:
    Ui::Zadacha *ui;
    QVBoxLayout* mainLayout;
    QCustomPlot* graphics;
    QCustomPlot* maxErr1;
    QCustomPlot* maxErr2;
    QLineEdit* start_p;
    QLineEdit* finish_p;
    QLineEdit* step;
    QLabel* max_z1;
    QLabel* max_z2;
    QLabel* optimal_t_s;
    QCustomPlot* maximum_z;
};

#endif // ZADACHA_H
