#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myclass.h"
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_head(0), m_tail(0), m_average(0), m_class(new MyClass), m_thread(new QThread), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(m_class, SIGNAL(send(bool)), this, SLOT(update(bool)));
    connect(m_thread, SIGNAL(started()), m_class, SLOT(doWork()));
    connect(m_class, SIGNAL(finished()), m_thread, SLOT(quit()));
    m_class->moveToThread(m_thread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    m_thread->start();
}

void MainWindow::update(bool flag){
    m_average += 1;
    ui->label->setText("Количество опытов: " + QString::number(m_average));
    if(flag){
        ui->label_2->setText(QString::number(++m_tail));
    } else{
        ui->label_3->setText(QString::number(++m_head));
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_class->setrunning(false);
}
