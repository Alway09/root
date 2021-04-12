#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), m_width_playground(new QLineEdit("800")), m_height_playground(new QLineEdit("600"))
{
    setFixedSize(300, 300);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QPushButton* startButton = new QPushButton("Start Game");
    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGameButtonClicked);

    QPushButton* exitButton = new QPushButton("Exit");
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    QPushButton* settingsButton = new QPushButton("Settings");
    connect(settingsButton, &QPushButton::clicked, this, &MainMenu::settingsButtonClicked);

    mainLayout->addWidget(startButton);
    mainLayout->addWidget(settingsButton);
    mainLayout->addWidget(exitButton);
    setLayout(mainLayout);
}

void MainMenu::startGameButtonClicked(){
    Playground* pg = new Playground(m_width_playground->text().toInt(), m_height_playground->text().toInt(), this);
    pg->show();
    hide();
}

void MainMenu::settingsButtonClicked(){
    Settings* sets = new Settings(this);
    sets->show();
    hide();
}
