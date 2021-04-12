#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_creator(new GraphicCreator(this))
{
    QMenuBar* menubar = new QMenuBar(this);
    setMenuBar(menubar);
    menubar->addAction("Создать график", this, &MainWindow::createGraphicPressed);

    QWidget* central_widget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout;

    CoordinatePlane* p = new CoordinatePlane();
    m_plane = p;

    PlaneContainer* c = new PlaneContainer(p, this);
    m_container = c;
    connect(p, &CoordinatePlane::sizeChanged, c, &PlaneContainer::planeSizeChanged);
    connect(m_plane, &CoordinatePlane::helpLinesFlagChanged, m_container, &PlaneContainer::planeHelpLinesFlagChanged);

    connect(m_creator, &GraphicCreator::created, this, &MainWindow::openFile);
    connect(m_creator, &GraphicCreator::to_plane, m_container, &PlaneContainer::centerize);

    mainLayout->addWidget(c);
    central_widget->setLayout(mainLayout);
    setCentralWidget(central_widget);
}

MainWindow::~MainWindow()
{
    if(m_plane){
        delete m_plane;
    }
}

void MainWindow::createGraphicPressed(){
    //GraphicCreator gr(this);
    //connect(&gr, &GraphicCreator::created, this, &MainWindow::openFile);
    //connect(&gr, &GraphicCreator::to_plane, m_container, &PlaneContainer::centerize);
    //gr.exec();

    m_creator->exec();
}

void MainWindow::openFile(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this, "Файл", "Невозможно открыть файл, содержащий график!");
        return;
    }

    QByteArray* data = new QByteArray(file.readAll());
    QJsonDocument* jDoc = new QJsonDocument(QJsonDocument::fromJson(*data));
    file.close();
    delete data;

    m_plane->setData(jDoc);
}
