#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mnk.h"
#include "interpolation.h"
#include "newton.h"

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


void MainWindow::on_openMNK_clicked()
{
    MNK windowM;
    windowM.setModal(true);
    windowM.exec();
}

void MainWindow::on_openInterpol_clicked()
{
    Interpolation windowI;
    windowI.setModal(true);
    windowI.exec();
}

void MainWindow::on_openNew_clicked()
{
    Newton windowN;
    windowN.setModal(true);
    windowN.exec();
}
