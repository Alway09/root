#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QMouseEvent>
#include <QLabel>
#include <typeinfo>
#include "coordianteplane.h"
#include "planecontainer.h"
#include "graphiccreator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createGraphicPressed();
    void openFile(QString filename);

private:
    CoordinatePlane* m_plane;
    PlaneContainer* m_container;
    GraphicCreator* m_creator;
};
#endif // MAINWINDOW_H
