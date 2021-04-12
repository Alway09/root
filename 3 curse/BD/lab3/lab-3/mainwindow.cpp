#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(initDB() == 1){
        exit(EXIT_FAILURE);
    }
    initCB();
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::initDB(){
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString filename("../base.db");
    m_database.setDatabaseName(filename);

    if(QFileInfo::exists(filename)){
        m_database.open();
        m_database.exec("pragma foreign_keys=on");
    } else{
        QMessageBox::critical(this, "Critical error", "Can not open database");
        return 1;
    }

    //-----------------------
    m_Plan = new QSqlRelationalTableModel(nullptr, m_database);
    m_Plan->setTable("Plan");
    m_Plan->select();

    m_Plan->setRelation(2, QSqlRelation("Status", "ID_status", "name_status"));
    m_Plan->setRelation(5, QSqlRelation("Forma_obucheniya", "ID_forma", "name_forma"));
    m_Plan->setRelation(3, QSqlRelation("Specialnost", "ID_spec", "name_spec"));
    m_Plan->setRelation(4, QSqlRelation("Spez", "ID_spez", "name_spez"));
    m_Plan->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    ui->Plan_Plan->setItemDelegate(new QSqlRelationalDelegate(ui->Plan_Plan));

    ui->Plan_Plan->setModel(m_Plan);
    ui->Plan_Plan->setColumnHidden(1, true);
    m_Plan->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Status = new QSqlRelationalTableModel(nullptr, m_database);
    m_Status->setTable("Status");
    m_Status->select();
    ui->Status_2->setModel(m_Status);
    ui->Status_2->setColumnHidden(1, true);
    m_Status->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Specialnost = new QSqlRelationalTableModel(nullptr, m_database);
    m_Specialnost->setTable("Specialnost");
    m_Specialnost->select();

    m_Specialnost->setRelation(2, QSqlRelation("Kafedra", "ID_kaf", "name_kaf"));
    //m_Specialnost->setRelation(2, QSqlRelation("Spez", "ID_spez", "name_spez"));
    ui->Spec_Spec->setItemDelegate(new QSqlRelationalDelegate(ui->Spec_Spec));

    ui->Spec_Spec->setModel(m_Specialnost);
    m_Specialnost->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Spez = new QSqlRelationalTableModel(nullptr, m_database);
    m_Spez->setTable("Spez");
    m_Spez->select();
    ui->Spez1->setModel(m_Spez);
    m_Spez->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Potok = new QSqlRelationalTableModel(nullptr, m_database);
    m_Potok->setTable("Potok");
    m_Potok->select();

    //m_Potok->setRelation(3, QSqlRelation("Plan", "ID_plan", "name_plan"));
    //ui->Potok_Potok->setItemDelegate(new QSqlRelationalDelegate(ui->Potok_Potok));

    ui->Potok_Potok->setModel(m_Potok);
    ui->Potok_Potok->setColumnHidden(2, true);
    ui->Potok_Potok->setColumnHidden(3, true);
    m_Potok->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Kafedra = new QSqlRelationalTableModel(nullptr, m_database);
    m_Kafedra->setTable("Kafedra");
    m_Kafedra->select();
    ui->Kaf->setModel(m_Kafedra);
    ui->Kaf->setColumnHidden(1, true);
    m_Kafedra->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------
    m_Forma_obucheniya = new QSqlRelationalTableModel(nullptr, m_database);
    m_Forma_obucheniya->setTable("Forma_obucheniya");
    m_Forma_obucheniya->select();
    ui->Forma->setModel(m_Forma_obucheniya);
    ui->Forma->setColumnHidden(1, true);
    m_Forma_obucheniya->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //-----------------------

    updateDB();

    return 0;
}

void MainWindow::updateDB(){
    m_Plan->select();
    m_Plan->relationModel(2)->select();
    m_Plan->relationModel(3)->select();
    m_Plan->relationModel(5)->select();

    m_Specialnost->select();
    m_Specialnost->relationModel(2)->select();

    //m_Potok->select();
    //m_Potok->relationModel(3)->select();
}

void MainWindow::initCB(){
    ui->PotokCoosePlan->setModel(m_Plan);
    ui->PotokCoosePlan->setModelColumn(0);
    ui->PotokCoosePlan->setCurrentIndex(0);

    for(int i = 1990; i <= 1999; ++i){
        ui->PlanCooseYear->addItem(QString::number(i));
    }
    ui->PlanCooseYear->setCurrentIndex(9);

    for(int i = 2; i <= 8; ++i){
        ui->PlanChooseDuration->addItem(QString::number(i));
    }
    ui->PlanChooseDuration->setCurrentIndex(0);

}

bool MainWindow::testPotokCB(){
    bool b(true);

    b = b && (ui->PotokCoosePlan->currentIndex() >= 0);

    return b;
}

bool MainWindow::testPlanCB(){
    bool b(true);

    b = b && (ui->PlanCooseYear->currentIndex() >= 0);
    b = b && (ui->PlanChooseDuration->currentIndex() >= 0);

    return b;
}

void MainWindow::updatePotokFilter(){
    m_Potok->setFilter("");
    if(!testPotokCB()){
        return;
    }

    int ind(ui->PotokCoosePlan->currentIndex());
    QString stPlan(m_Plan->record(ind).field("ID_plan").value().toString());

    QString stFilter("(ID_plan=" + stPlan + ")");

    m_Potok->setFilter(stFilter);
}

void MainWindow::updatePlanFilter(){
    m_Plan->setFilter("");
    if(!testPlanCB()){
        return;
    }

    QString stYear(ui->PlanCooseYear->currentText());
    QString stDur(ui->PlanChooseDuration->currentText());

    QString stFilter("(add_year=" + stYear + ") and");
    stFilter += "(duration=" + stDur + ")";

    m_Plan->setFilter(stFilter);
}

void MainWindow::fillPotokRecord(QSqlRecord& rec){
    int curPlan(m_Potok->record(0).field("ID_plan").value().toInt());

    rec = m_Potok->record();
    rec.setValue("ID_plan", curPlan);
}

void MainWindow::fillPlanRecord(QSqlRecord &rec){
    int curYear(ui->PlanCooseYear->currentText().toInt());
    int curDur(ui->PlanChooseDuration->currentText().toInt());

    rec = m_Plan->record();
    rec.setValue("add_year", curYear);
    rec.setValue("duration", curDur);
}

void MainWindow::on_Plan_addB_clicked()
{
    QSqlRecord rec;
    if(!testPlanCB()){
        return;
    }

    fillPlanRecord(rec);
    m_Plan->insertRecord(-1, rec);
}

void MainWindow::on_Plan_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Plan_Plan->selectionModel()->currentIndex().isValid()){
        int row(ui->Plan_Plan->selectionModel()->currentIndex().row());
        m_Plan->removeRow(row);
    }
}

void MainWindow::on_Plan_acceptB_clicked()
{
    if(m_Plan->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Plan->lastError().databaseText());
    }
}

void MainWindow::on_Plan_cancelB_clicked()
{
    m_Plan->revertAll();
}

void MainWindow::on_Status_addB_clicked()
{
    QSqlRecord rec;
    m_Status->insertRecord(-1, rec);
}

void MainWindow::on_Status_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Status_2->selectionModel()->currentIndex().isValid()){
        int row(ui->Status_2->selectionModel()->currentIndex().row());
        m_Status->removeRow(row);
    }
}

void MainWindow::on_Status_acceptB_clicked()
{
    if(m_Status->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Status->lastError().databaseText());
    }
}

void MainWindow::on_Status_cancelB_clicked()
{
    m_Status->revertAll();
}

void MainWindow::on_Specialnost_addB_clicked()
{
    QSqlRecord rec;
    m_Specialnost->insertRecord(-1, rec);
}

void MainWindow::on_Specialnost_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Spec_Spec->selectionModel()->currentIndex().isValid()){
        int row(ui->Spec_Spec->selectionModel()->currentIndex().row());
        m_Specialnost->removeRow(row);
    }
}

void MainWindow::on_Specialnost_acceptB_clicked()
{
    if(m_Specialnost->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Specialnost->lastError().databaseText());
    }
}

void MainWindow::on_Specialnost_cancelB_clicked()
{
    m_Specialnost->revertAll();
}

void MainWindow::on_Spez_addB_clicked()
{
    QSqlRecord rec;
    m_Spez->insertRecord(-1, rec);
}

void MainWindow::on_Spez_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Spez1->selectionModel()->currentIndex().isValid()){
        int row(ui->Spez1->selectionModel()->currentIndex().row());
        m_Spez->removeRow(row);
    }
}

void MainWindow::on_Spez_acceptB_clicked()
{
    if(m_Spez->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Spez->lastError().databaseText());
    }
}

void MainWindow::on_Spez_cancelB_clicked()
{
    m_Spez->revertAll();
}

void MainWindow::on_Potok_addB_clicked()
{
    QSqlRecord rec;
    if(!testPotokCB()) return;

    if(m_Potok->filter() != "")
        fillPotokRecord(rec);

    m_Potok->insertRecord(-1, rec);
}

void MainWindow::on_Potok_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Potok_Potok->selectionModel()->currentIndex().isValid()){
        int row(ui->Potok_Potok->selectionModel()->currentIndex().row());
        m_Potok->removeRow(row);
    }
}

void MainWindow::on_Potok_acceptB_5_clicked()
{
    if(m_Potok->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Potok->lastError().databaseText());
    }
}

void MainWindow::on_Potok_cancelB_clicked()
{
    m_Potok->revertAll();
}

void MainWindow::on_Kafedra_addB_clicked()
{
    QSqlRecord rec;
    m_Kafedra->insertRecord(-1, rec);
}

void MainWindow::on_Kafedra_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Kaf->selectionModel()->currentIndex().isValid()){
        int row(ui->Kaf->selectionModel()->currentIndex().row());
        m_Kafedra->removeRow(row);
    }
}

void MainWindow::on_Kafedra_acceptB_clicked()
{
    if(m_Kafedra->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Kafedra->lastError().databaseText());
    }
}

void MainWindow::on_Kafedra_cancelB_clicked()
{
    m_Kafedra->revertAll();
}

void MainWindow::on_Forma_addB_clicked()
{
    QSqlRecord rec;
    m_Forma_obucheniya->insertRecord(-1, rec);
}

void MainWindow::on_Forma_deleteB_clicked()
{
    if(!warningDialog()) return;

    if(ui->Forma->selectionModel()->currentIndex().isValid()){
        int row(ui->Forma->selectionModel()->currentIndex().row());
        m_Forma_obucheniya->removeRow(row);
    }
}

void MainWindow::on_Forma_acceptB_clicked()
{
    if(m_Forma_obucheniya->submitAll()){
        updateDB();
    } else{
        QMessageBox::warning(this, "Error", m_Forma_obucheniya->lastError().databaseText());
    }
}

void MainWindow::on_Forma_cancelB_clicked()
{
    m_Forma_obucheniya->revertAll();
}

void MainWindow::on_PotokCoosePlan_currentIndexChanged(int)
{
    updatePotokFilter();
}

void MainWindow::on_PlanCooseYear_currentIndexChanged(int)
{
    updatePlanFilter();
}

void MainWindow::on_PlanChooseDuration_currentIndexChanged(int)
{
    updatePlanFilter();
}

bool MainWindow::warningDialog(){
    QMessageBox msg;
    msg.setText("Удаление");
    msg.setInformativeText("Возможна потеря данных. Продолжить?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);
    msg.setEscapeButton(QMessageBox::No);
    int ans(msg.exec());

    return ans == QMessageBox::Yes;
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 4){
        m_Plan->setFilter("");
    } else if(index == 0){
        updatePlanFilter();
    }
}
