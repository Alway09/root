#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinateplane.h"
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#include <QMessageBox>
#include <math.h>

//-------------------------------------------------------------
using Points = QVector<QPair<double, double> >;
//-------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_graphic(nullptr)
{
    ui->setupUi(this);
    m_graphic = new CoordinatePlane(this);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    QWidget* centralWidget = new QWidget;

    QPushButton* open = new QPushButton("Открыть");
    connect(open, SIGNAL(clicked()), this, SLOT(openJson()));

    mainLayout->addWidget(m_graphic->getScrollArea());
    mainLayout->addWidget(open);


    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool jsonIsValid(QJsonDocument* jDoc){
    if(jDoc->isArray())
    {
        QJsonArray array = jDoc->array();
        if(array.size() && array[0].type() == QJsonValue::Object)
        {
            QStringList list(array[0].toObject().keys());
            if(list.size() == 3 && list[0] == "azimuth" && list[1] ==  "depth" && list[2] == "inclination")
            {
                return true;
            }
        }
    }
    return false;
}

QVector<QPair<double, double>>* transform(QWidget* parent, QJsonDocument* jDoc){
    if(jsonIsValid(jDoc)){
        Points* dots = new Points;
        QJsonArray array = jDoc->array();
        QJsonArray::const_iterator iter(array.constBegin());
        while(iter != array.constEnd()){
            dots->push_back(QPair<double, double>(iter->toObject()["depth"].toDouble() * cos(iter->toObject()["azimuth"].toDouble()) * sin(iter->toObject()["inclination"].toDouble()),\
                                                  iter->toObject()["depth"].toDouble() * cos(iter->toObject()["inclination"].toDouble())));
            ++iter;
        }
        return dots;
    } else{
        QMessageBox::critical(parent, "Ошибка", "Неподходящий файл!");
    }
    return nullptr;
}

void MainWindow::openJson(){
    QFileDialog* dialog = new QFileDialog();
    QStringList full_name = dialog->getOpenFileNames(this, "Выберите файл", "", tr("JSON files (*.json)"));

    if(!full_name.size()){
        return;
    } else if(full_name.size() > 1){
        QMessageBox::warning(this, "Внимание", "Нужно выбрать один файл!");
    } else{
        QFile file(full_name[0]);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen()){
            QByteArray array(file.readAll());
            QJsonDocument* jDoc = new QJsonDocument(QJsonDocument::fromJson(array));
            m_graphic->setData(*transform(this, jDoc));
        } else{
            QMessageBox::critical(this, "Ошибка", "Файл не может быть открыт!");
        }
        file.close();
    }
}

