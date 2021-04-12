#ifndef METHOD_H
#define METHOD_H

#include <QDialog>
#include<QVector>
#include<QLineEdit>
#include<QTextEdit>
#include"matrixd.h"
#include"qcustomplot.h"
#include"scene.h"

namespace Ui {
class Method;
}

class Method : public QDialog
{
    Q_OBJECT

public:
    explicit Method(QWidget *parent = nullptr,int am_of_ci = 2, bool chbx_2 = false);
    ~Method();
    void commivoyager(MatrixD);

private slots:
    void backButtont_clicked();
    void calculateButton_clicked();
    void calculate_button_clicked();
    void clearButtont_clicked();
    void againButtont_clicked();

private:
    Ui::Method *ui;
    QTextEdit* textEdit;
    QVector<QLineEdit*> lines_vector;
    int amount_of_cities;
    QLineEdit* start_point;
    QCustomPlot* graphic;
    Scene* scene;
    QGraphicsView* view;
};

#endif // METHOD_H
