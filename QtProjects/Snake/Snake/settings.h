#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPair>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent);
    ~Settings();
    bool createDefaultJsonFile();

public slots:
    void backButtonClicked();
    void unstandartSizesCheckChanged();

private:
    QWidget* m_parent;
    QJsonDocument* m_settings_document;
    QPair<QLineEdit*, QLineEdit*> m_unstandart_sizes;
    QCheckBox* m_unstandart_sizes_check_box;

};

#endif // SETTINGS_H
