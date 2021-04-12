#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"zadacha.h"

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
    Zadacha* window = new Zadacha(this, true);
    window->setModal(true);
    window->exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Zadacha* window = new Zadacha(this, false);
    window->setModal(true);
    window->exec();
}
