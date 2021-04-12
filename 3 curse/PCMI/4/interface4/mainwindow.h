#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>
#include <QList>
#include <QTime>
#include <QDebug>
#include <string>

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

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_nextButton_clicked();

    void on_cancelButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    int timeStart;
    int countPanels;
    int experiment = 1;
    float k;
    bool bold;
    bool italic;
    bool line;
    int numberClick = 0;
    int average = 0;
    void initCB();
    void changeCountPanels();
    void addTextToPanels();
    void removePanelText();
    void StartTest();
    void StopTest();
    QList<QString> randomPanels();
    bool t;
    void PanelClicked();
    void saveLog(int det);
    void moveCursor();
    QTime timer;
};
#endif // MAINWINDOW_H
