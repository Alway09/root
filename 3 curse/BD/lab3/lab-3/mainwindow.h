#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int initDB();
    void initCB();
    bool testPotokCB();
    bool testPlanCB();
    void updatePotokFilter();
    void updatePlanFilter();
    void fillPotokRecord(QSqlRecord& rec);
    void fillPlanRecord(QSqlRecord& rec);
    void updateDB();
    bool warningDialog();

private slots:
    void on_Plan_addB_clicked();

    void on_Plan_deleteB_clicked();

    void on_Plan_acceptB_clicked();

    void on_Plan_cancelB_clicked();

    void on_Status_addB_clicked();

    void on_Status_deleteB_clicked();

    void on_Status_acceptB_clicked();

    void on_Status_cancelB_clicked();

    void on_Specialnost_addB_clicked();

    void on_Specialnost_deleteB_clicked();

    void on_Specialnost_acceptB_clicked();

    void on_Specialnost_cancelB_clicked();

    void on_Spez_addB_clicked();

    void on_Spez_deleteB_clicked();

    void on_Spez_acceptB_clicked();

    void on_Spez_cancelB_clicked();

    void on_Potok_addB_clicked();

    void on_Potok_deleteB_clicked();

    void on_Potok_acceptB_5_clicked();

    void on_Potok_cancelB_clicked();

    void on_Kafedra_addB_clicked();

    void on_Kafedra_deleteB_clicked();

    void on_Kafedra_acceptB_clicked();

    void on_Kafedra_cancelB_clicked();

    void on_Forma_addB_clicked();

    void on_Forma_deleteB_clicked();

    void on_Forma_acceptB_clicked();

    void on_Forma_cancelB_clicked();

    void on_PotokCoosePlan_currentIndexChanged(int index);

    void on_PlanCooseYear_currentIndexChanged(int index);

    void on_PlanChooseDuration_currentIndexChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;

    QSqlDatabase m_database;
    QSqlRelationalTableModel *m_Plan, *m_Status, *m_Specialnost, *m_Spez, *m_Potok, *m_Kafedra, *m_Forma_obucheniya;
};
#endif // MAINWINDOW_H
