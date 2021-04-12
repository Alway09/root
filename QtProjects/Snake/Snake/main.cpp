#include <QApplication>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include "head.h"
#include "body.h"
#include "playground.h"
#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setDesktopSettingsAware(false);

    MainMenu* menu = new MainMenu();
    menu->show();

    return a.exec();
}
