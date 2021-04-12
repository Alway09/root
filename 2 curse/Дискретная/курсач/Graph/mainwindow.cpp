#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "method.h"
#include<QMessageBox>

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

void MainWindow::on_pushButton_clicked()
{
    int am_of_ci = ui->lineEdit->text().toInt();
    if(am_of_ci < 3){
        QMessageBox::critical(this, "Ошибка", "Введенное количество городов не может быть меньше 3-х");
        return;
    } else if(am_of_ci > 27){
        QMessageBox::critical(this, "Ошибка", "Работа с большим числом городов не удобна в этом режиме");
        return;
    }
    Method* wind = new Method(this, am_of_ci, ui->checkBox_2->isChecked());
    wind->setModal(true);
    wind->exec();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->lineEdit->setDisabled(false);
    } else if(arg1 == 2){
        ui->lineEdit->setDisabled(true);
    }
}
