#ifndef GRAPHICCREATOR_H
#define GRAPHICCREATOR_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPair>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QPair>
#include <cmath>
#include <QCheckBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QMessageBox>
#include <QLocale>
#include <QToolTip>
#include "abstractfunction.h"
#include "cartesianfunctions.h"
#include "polarfunctions.h"

class GraphicCreator : public QDialog
{
    Q_OBJECT

public:
    GraphicCreator(QWidget* parent = nullptr);
    ~GraphicCreator();

    void initFunctions();

public slots:
    void openFileButtonClicked();
    void createButtonClicked();
    void backButtonClicked();
    void cartesianChBStateChanged(int state);
    void polarChBStateChanged(int state);

signals:
    void created(QString filename);
    void to_plane();

private:
    QVector<AbstractFunction*> m_cartesianFunctions;
    QVector<AbstractFunction*> m_polarFunctions;
    QComboBox* m_cartesian_graphCB;
    QComboBox* m_polar_graphCB;
    QPair<QLineEdit*, QLineEdit*> m_borders;
    QLineEdit* m_step;
    QCheckBox* m_save_or_not;
    QCheckBox* m_cartesian_check;
    QCheckBox* m_polar_check;
    QDoubleValidator* m_borders_validator;
    QDoubleValidator* m_step_validator;
};

#endif // GRAPHICCREATOR_H
