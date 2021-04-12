#include "settings.h"

static const QString filename("settings.json");

Settings::Settings(QWidget *parent) : QWidget(), m_parent(parent), m_settings_document(nullptr),
    m_unstandart_sizes(new QLineEdit("0"), new QLineEdit("0")),
    m_unstandart_sizes_check_box(new QCheckBox("Unstandart sizes"))
{
    QFile* json_file = new QFile(filename);
    if(json_file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray array(json_file->readAll());
        m_settings_document = new QJsonDocument(QJsonDocument::fromJson(array));
    } else{
        QMessageBox::warning(this, "Settings file", "User settings file not found!\n Default file created.");
        if(!createDefaultJsonFile()){
            QMessageBox::critical(this, "Settings file", "Can not create settings file!");
        }
    }
    json_file->close();

    setFixedSize(m_parent->width(), m_parent->height());
    setWindowTitle("Settings");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* sizeBoxLayout = new QVBoxLayout;
    QHBoxLayout* unstandartSizesLayout = new QHBoxLayout;
    QHBoxLayout* unstandartWidthLayout = new QHBoxLayout;
    QHBoxLayout* unstandartHeightLayout = new QHBoxLayout;

    m_unstandart_sizes_check_box->setChecked(true);
    connect(m_unstandart_sizes_check_box, &QCheckBox::stateChanged, this, &Settings::unstandartSizesCheckChanged);

    QLabel* w = new QLabel("W: ");
    unstandartWidthLayout->addWidget(w);
    m_unstandart_sizes.first->setText(m_settings_document->object()["width"].toString());
    unstandartWidthLayout->addWidget(m_unstandart_sizes.first);

    QLabel* h = new QLabel("H: ");
    unstandartHeightLayout->addWidget(h);
    unstandartHeightLayout->addWidget(m_unstandart_sizes.second);
    unstandartSizesLayout->addLayout(unstandartWidthLayout);
    unstandartSizesLayout->addLayout(unstandartHeightLayout);

    QGroupBox* size = new QGroupBox("Resolution");
    sizeBoxLayout->addWidget(m_unstandart_sizes_check_box);
    sizeBoxLayout->addLayout(unstandartSizesLayout);
    size->setLayout(sizeBoxLayout);

    QPushButton* backButton = new QPushButton("Back");
    connect(backButton, &QPushButton::clicked, this, &Settings::backButtonClicked);

    mainLayout->addWidget(size);
    mainLayout->addWidget(backButton);
    setLayout(mainLayout);
}

Settings::~Settings(){
    delete m_unstandart_sizes.first;
    delete m_unstandart_sizes.second;
}

void Settings::backButtonClicked(){
    m_parent->show();
    close();
}

void Settings::unstandartSizesCheckChanged(){
    if(!m_unstandart_sizes_check_box->isChecked()){
        m_unstandart_sizes.first->setEnabled(false);
        m_unstandart_sizes.second->setEnabled(false);
    } else{
        m_unstandart_sizes.first->setEnabled(true);
        m_unstandart_sizes.second->setEnabled(true);
    }
}

bool Settings::createDefaultJsonFile(){
    const char data[] =
"{\n\
    \"width\": \"640\"\
    \"unstandartSizes\" :\n\
        {\n\
            \"width\": 640\n\
            \"height\": 480\n\
        }\n\
}\0";

    QFile* json_file = new QFile(filename);
    if(json_file->open(QIODevice::WriteOnly | QIODevice::Text)){
        if(json_file->write(data) == -1){
            return false;
        }
    } else{
        return false;
    }

    QByteArray array(json_file->readAll());
    m_settings_document = new QJsonDocument(QJsonDocument::fromJson(array));

    json_file->close();
    return true;
}
