#include "mainwindow1.h"
#include "ui_mainwindow1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(initDB() == 1){
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::initDB(){
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString filename("../base.bd");
    m_database.setDatabaseName(filename);

    if(QFileInfo::exists(filename)){
        m_database.open();
        m_database.exec("pragma foreign_keys=on");
    } else{
        QMessageBox::critical(this, "Critical error", "Can not open database");
        return 1;
    }

    //-----------------------
    m_Plan = new QSqlTableModel(nullptr, m_database);
    m_Plan->setTable("Plan");
    m_Plan->select();
    ui->Plan_Plan->setModel(m_Plan);
    m_Plan->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_Status_SUB = new QSqlQueryModel;
    ui->Plan_Status->setModel(m_Status_SUB);

    m_Specialnost_SUB = new QSqlQueryModel;
    ui->Plan_Specialnost->setModel(m_Specialnost_SUB);

    m_Forma_obucheniya_SUB = new QSqlQueryModel;
    ui->Plan_Forma->setModel(m_Forma_obucheniya_SUB);
    //-----------------------
    m_Status = new QSqlTableModel(nullptr, m_database);
    m_Status->setTable("Status");
    m_Status->select();
    ui->Status_2->setModel(m_Status);
    m_Status->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //-----------------------
    m_Specialnost = new QSqlTableModel(nullptr, m_database);
    m_Specialnost->setTable("Specialnost");
    m_Specialnost->select();
    ui->Spec_Spec->setModel(m_Specialnost);
    m_Specialnost->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_Spez_SUB = new QSqlQueryModel;
    ui->Spec_Spez->setModel(m_Spez_SUB);

    m_Kafedra_SUB = new QSqlQueryModel;
    ui->Spec_Kaf->setModel(m_Kafedra_SUB);
    //-----------------------
    m_Spez = new QSqlTableModel(nullptr, m_database);
    m_Spez->setTable("Spez");
    m_Spez->select();
    ui->Spez1->setModel(m_Spez);
    m_Spez->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //-----------------------
    m_Potok = new QSqlTableModel(nullptr, m_database);
    m_Potok->setTable("Potok");
    m_Potok->select();
    ui->Potok_Potok->setModel(m_Potok);
    m_Potok->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_Plan_SUB = new QSqlQueryModel;
    ui->Potok_Plan->setModel(m_Plan_SUB);
    //-----------------------
    m_Kafedra = new QSqlTableModel(nullptr, m_database);
    m_Kafedra->setTable("Kafedra");
    m_Kafedra->select();
    ui->Kaf->setModel(m_Kafedra);
    m_Kafedra->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //-----------------------
    m_Forma_obucheniya = new QSqlTableModel(nullptr, m_database);
    m_Forma_obucheniya->setTable("Forma_obucheniya");
    m_Forma_obucheniya->select();
    ui->Forma->setModel(m_Forma_obucheniya);
    m_Forma_obucheniya->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //-----------------------

    updateDB();

    return 0;
}

void MainWindow::updateDB(){
    m_Status_SUB->setQuery("SELECT * FROM Status", m_database);
    m_Specialnost_SUB->setQuery("SELECT * FROM Specialnost", m_database);
    m_Forma_obucheniya_SUB->setQuery("SELECT * FROM Forma_obucheniya", m_database);
    m_Spez_SUB->setQuery("SELECT * FROM Spez", m_database);
    m_Kafedra_SUB->setQuery("SELECT * FROM Kafedra", m_database);
    m_Plan_SUB->setQuery("SELECT * FROM Plan", m_database);
}

void MainWindow::on_Plan_addB_clicked()
{
    QSqlRecord rec;
    m_Plan->insertRecord(-1, rec);
}

void MainWindow::on_Plan_deleteB_clicked()
{
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
    m_Potok->insertRecord(-1, rec);
}

void MainWindow::on_Potok_deleteB_clicked()
{
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
