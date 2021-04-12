#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"
#include "myclass.h"

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
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    //void on_pushButton_2_clicked();

public slots:
    void update(bool);

private:
    unsigned long long m_head;
    unsigned long long m_tail;
    unsigned long long m_average;
    MyClass* m_class;
    QThread* m_thread;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
