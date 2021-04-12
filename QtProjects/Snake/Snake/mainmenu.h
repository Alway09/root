#ifndef MAINMENU_H
#define MAINMENU_H

#include<QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"playground.h"
#include"settings.h"

class MainMenu : public QWidget
{
public:
    explicit MainMenu(QWidget *parent = nullptr);

public slots:
    void startGameButtonClicked();
    void settingsButtonClicked();

private:
    QLineEdit* m_width_playground;
    QLineEdit* m_height_playground;

};

#endif // MAINMENU_H
