#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <cmath>
#include <QVector>
#include <QStringList>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QFile>
#include <QLabel>
#include <QComboBox>
#include <QDebug>
#include "button.h"
#include "button1.h"
#include "workarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;
    void placeButton(Button* b, WorkArea* area);
    void placeButton1(Button1* b, WorkArea* area);
    void timerEvent(QTimerEvent* timer) override;
    void setButtonColor(int index);
    void setAreaColor(int index);

public slots:
    void s_buttonClicked();
    void save_buttonClicked();
    void trigger_buttonClicked();
    void workArea_mouseClicked(bool late);
    void clear_buttonClicked();
    void firstExpCheckChanged(int state);
    void secondExpCheckChanged(int state);
    void thirdExp1CheckChanged(int state);
    void fourthExp1CheckChanged(int state);
    void fourthExp2CheckChanged(int state);

private:
    Ui::MainWindow *ui;
    Button *m_button;
    Button1* m_button1;
    WorkArea* m_zad11workArea;
    QLineEdit* m_S_LE;
    QLineEdit* m_D_LE;
    QLineEdit* m_h_LE;
    QLineEdit* m_filename;
    QTextEdit* m_results;
    QCheckBox* m_first_exp;
    QCheckBox* m_second_exp;
    QCheckBox* m_third_exp1;
    //QCheckBox* m_third_exp2;
    QCheckBox* m_fourth_exp1;
    QCheckBox* m_fourth_exp2;
    QComboBox* m_bg_colors_CB;
    QComboBox* m_but_colors_CB;
    QComboBox* m_button_pos;
    QVector<int> m_colormem;
    int m_distance;
    int m_timer_id;
    u_int m_milliseconds;
    u_int m_counter;
    u_int m_missing_counter;
    u_int m_top_exp;
    u_int m_average_time;
};
#endif // MAINWINDOW_H
