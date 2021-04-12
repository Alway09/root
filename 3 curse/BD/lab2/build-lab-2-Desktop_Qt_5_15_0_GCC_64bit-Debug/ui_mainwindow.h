/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *Plan;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *Plan_Plan;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableView *Plan_Status;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableView *Plan_Specialnost;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QTableView *Plan_Forma;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *Plan_addB;
    QPushButton *Plan_deleteB;
    QPushButton *Plan_acceptB;
    QPushButton *Plan_cancelB;
    QWidget *Status;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QTableView *Status_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Status_addB;
    QPushButton *Status_deleteB;
    QPushButton *Status_acceptB;
    QPushButton *Status_cancelB;
    QWidget *Specialnost;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QTableView *Spec_Spec;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QTableView *Spec_Spez;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QTableView *Spec_Kaf;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *Specialnost_addB;
    QPushButton *Specialnost_deleteB;
    QPushButton *Specialnost_acceptB;
    QPushButton *Specialnost_cancelB;
    QWidget *Spez;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QTableView *Spez1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Spez_addB;
    QPushButton *Spez_deleteB;
    QPushButton *Spez_acceptB;
    QPushButton *Spez_cancelB;
    QWidget *Potok;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QTableView *Potok_Potok;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_11;
    QTableView *Potok_Plan;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *Potok_addB;
    QPushButton *Potok_deleteB;
    QPushButton *Potok_acceptB_5;
    QPushButton *Potok_cancelB;
    QWidget *Kafedra;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_12;
    QTableView *Kaf;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *Kafedra_addB;
    QPushButton *Kafedra_deleteB;
    QPushButton *Kafedra_acceptB;
    QPushButton *Kafedra_cancelB;
    QWidget *Forma_obucheniya;
    QVBoxLayout *verticalLayout_20;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_13;
    QTableView *Forma;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *Forma_addB;
    QPushButton *Forma_deleteB;
    QPushButton *Forma_acceptB;
    QPushButton *Forma_cancelB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1304, 454);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Plan = new QWidget();
        Plan->setObjectName(QString::fromUtf8("Plan"));
        verticalLayout_14 = new QVBoxLayout(Plan);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Plan);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        Plan_Plan = new QTableView(Plan);
        Plan_Plan->setObjectName(QString::fromUtf8("Plan_Plan"));

        verticalLayout->addWidget(Plan_Plan);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(Plan);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        Plan_Status = new QTableView(Plan);
        Plan_Status->setObjectName(QString::fromUtf8("Plan_Status"));

        verticalLayout_2->addWidget(Plan_Status);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(Plan);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        Plan_Specialnost = new QTableView(Plan);
        Plan_Specialnost->setObjectName(QString::fromUtf8("Plan_Specialnost"));

        verticalLayout_3->addWidget(Plan_Specialnost);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(Plan);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);

        Plan_Forma = new QTableView(Plan);
        Plan_Forma->setObjectName(QString::fromUtf8("Plan_Forma"));

        verticalLayout_4->addWidget(Plan_Forma);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_14->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        Plan_addB = new QPushButton(Plan);
        Plan_addB->setObjectName(QString::fromUtf8("Plan_addB"));

        horizontalLayout_9->addWidget(Plan_addB);

        Plan_deleteB = new QPushButton(Plan);
        Plan_deleteB->setObjectName(QString::fromUtf8("Plan_deleteB"));

        horizontalLayout_9->addWidget(Plan_deleteB);

        Plan_acceptB = new QPushButton(Plan);
        Plan_acceptB->setObjectName(QString::fromUtf8("Plan_acceptB"));

        horizontalLayout_9->addWidget(Plan_acceptB);

        Plan_cancelB = new QPushButton(Plan);
        Plan_cancelB->setObjectName(QString::fromUtf8("Plan_cancelB"));

        horizontalLayout_9->addWidget(Plan_cancelB);


        verticalLayout_14->addLayout(horizontalLayout_9);

        tabWidget->addTab(Plan, QString());
        Status = new QWidget();
        Status->setObjectName(QString::fromUtf8("Status"));
        verticalLayout_15 = new QVBoxLayout(Status);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(Status);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        Status_2 = new QTableView(Status);
        Status_2->setObjectName(QString::fromUtf8("Status_2"));

        verticalLayout_5->addWidget(Status_2);


        verticalLayout_15->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Status_addB = new QPushButton(Status);
        Status_addB->setObjectName(QString::fromUtf8("Status_addB"));

        horizontalLayout_3->addWidget(Status_addB);

        Status_deleteB = new QPushButton(Status);
        Status_deleteB->setObjectName(QString::fromUtf8("Status_deleteB"));

        horizontalLayout_3->addWidget(Status_deleteB);

        Status_acceptB = new QPushButton(Status);
        Status_acceptB->setObjectName(QString::fromUtf8("Status_acceptB"));

        horizontalLayout_3->addWidget(Status_acceptB);

        Status_cancelB = new QPushButton(Status);
        Status_cancelB->setObjectName(QString::fromUtf8("Status_cancelB"));

        horizontalLayout_3->addWidget(Status_cancelB);


        verticalLayout_15->addLayout(horizontalLayout_3);

        tabWidget->addTab(Status, QString());
        Specialnost = new QWidget();
        Specialnost->setObjectName(QString::fromUtf8("Specialnost"));
        verticalLayout_16 = new QVBoxLayout(Specialnost);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_6 = new QLabel(Specialnost);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_6);

        Spec_Spec = new QTableView(Specialnost);
        Spec_Spec->setObjectName(QString::fromUtf8("Spec_Spec"));

        verticalLayout_6->addWidget(Spec_Spec);


        horizontalLayout_4->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_7 = new QLabel(Specialnost);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_7);

        Spec_Spez = new QTableView(Specialnost);
        Spec_Spez->setObjectName(QString::fromUtf8("Spec_Spez"));

        verticalLayout_7->addWidget(Spec_Spez);


        horizontalLayout_4->addLayout(verticalLayout_7);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_9 = new QLabel(Specialnost);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_9);

        Spec_Kaf = new QTableView(Specialnost);
        Spec_Kaf->setObjectName(QString::fromUtf8("Spec_Kaf"));

        verticalLayout_9->addWidget(Spec_Kaf);


        horizontalLayout_4->addLayout(verticalLayout_9);


        verticalLayout_16->addLayout(horizontalLayout_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        Specialnost_addB = new QPushButton(Specialnost);
        Specialnost_addB->setObjectName(QString::fromUtf8("Specialnost_addB"));

        horizontalLayout_10->addWidget(Specialnost_addB);

        Specialnost_deleteB = new QPushButton(Specialnost);
        Specialnost_deleteB->setObjectName(QString::fromUtf8("Specialnost_deleteB"));

        horizontalLayout_10->addWidget(Specialnost_deleteB);

        Specialnost_acceptB = new QPushButton(Specialnost);
        Specialnost_acceptB->setObjectName(QString::fromUtf8("Specialnost_acceptB"));

        horizontalLayout_10->addWidget(Specialnost_acceptB);

        Specialnost_cancelB = new QPushButton(Specialnost);
        Specialnost_cancelB->setObjectName(QString::fromUtf8("Specialnost_cancelB"));

        horizontalLayout_10->addWidget(Specialnost_cancelB);


        verticalLayout_16->addLayout(horizontalLayout_10);

        tabWidget->addTab(Specialnost, QString());
        Spez = new QWidget();
        Spez->setObjectName(QString::fromUtf8("Spez"));
        verticalLayout_17 = new QVBoxLayout(Spez);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_8 = new QLabel(Spez);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_8);

        Spez1 = new QTableView(Spez);
        Spez1->setObjectName(QString::fromUtf8("Spez1"));

        verticalLayout_8->addWidget(Spez1);


        verticalLayout_17->addLayout(verticalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Spez_addB = new QPushButton(Spez);
        Spez_addB->setObjectName(QString::fromUtf8("Spez_addB"));

        horizontalLayout_5->addWidget(Spez_addB);

        Spez_deleteB = new QPushButton(Spez);
        Spez_deleteB->setObjectName(QString::fromUtf8("Spez_deleteB"));

        horizontalLayout_5->addWidget(Spez_deleteB);

        Spez_acceptB = new QPushButton(Spez);
        Spez_acceptB->setObjectName(QString::fromUtf8("Spez_acceptB"));

        horizontalLayout_5->addWidget(Spez_acceptB);

        Spez_cancelB = new QPushButton(Spez);
        Spez_cancelB->setObjectName(QString::fromUtf8("Spez_cancelB"));

        horizontalLayout_5->addWidget(Spez_cancelB);


        verticalLayout_17->addLayout(horizontalLayout_5);

        tabWidget->addTab(Spez, QString());
        Potok = new QWidget();
        Potok->setObjectName(QString::fromUtf8("Potok"));
        verticalLayout_18 = new QVBoxLayout(Potok);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_10 = new QLabel(Potok);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_10);

        Potok_Potok = new QTableView(Potok);
        Potok_Potok->setObjectName(QString::fromUtf8("Potok_Potok"));

        verticalLayout_10->addWidget(Potok_Potok);


        horizontalLayout_11->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_11 = new QLabel(Potok);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_11);

        Potok_Plan = new QTableView(Potok);
        Potok_Plan->setObjectName(QString::fromUtf8("Potok_Plan"));

        verticalLayout_11->addWidget(Potok_Plan);


        horizontalLayout_11->addLayout(verticalLayout_11);


        verticalLayout_18->addLayout(horizontalLayout_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Potok_addB = new QPushButton(Potok);
        Potok_addB->setObjectName(QString::fromUtf8("Potok_addB"));

        horizontalLayout_6->addWidget(Potok_addB);

        Potok_deleteB = new QPushButton(Potok);
        Potok_deleteB->setObjectName(QString::fromUtf8("Potok_deleteB"));

        horizontalLayout_6->addWidget(Potok_deleteB);

        Potok_acceptB_5 = new QPushButton(Potok);
        Potok_acceptB_5->setObjectName(QString::fromUtf8("Potok_acceptB_5"));

        horizontalLayout_6->addWidget(Potok_acceptB_5);

        Potok_cancelB = new QPushButton(Potok);
        Potok_cancelB->setObjectName(QString::fromUtf8("Potok_cancelB"));

        horizontalLayout_6->addWidget(Potok_cancelB);


        verticalLayout_18->addLayout(horizontalLayout_6);

        tabWidget->addTab(Potok, QString());
        Kafedra = new QWidget();
        Kafedra->setObjectName(QString::fromUtf8("Kafedra"));
        verticalLayout_19 = new QVBoxLayout(Kafedra);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        label_12 = new QLabel(Kafedra);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_12);

        Kaf = new QTableView(Kafedra);
        Kaf->setObjectName(QString::fromUtf8("Kaf"));

        verticalLayout_12->addWidget(Kaf);


        verticalLayout_19->addLayout(verticalLayout_12);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Kafedra_addB = new QPushButton(Kafedra);
        Kafedra_addB->setObjectName(QString::fromUtf8("Kafedra_addB"));

        horizontalLayout_7->addWidget(Kafedra_addB);

        Kafedra_deleteB = new QPushButton(Kafedra);
        Kafedra_deleteB->setObjectName(QString::fromUtf8("Kafedra_deleteB"));

        horizontalLayout_7->addWidget(Kafedra_deleteB);

        Kafedra_acceptB = new QPushButton(Kafedra);
        Kafedra_acceptB->setObjectName(QString::fromUtf8("Kafedra_acceptB"));

        horizontalLayout_7->addWidget(Kafedra_acceptB);

        Kafedra_cancelB = new QPushButton(Kafedra);
        Kafedra_cancelB->setObjectName(QString::fromUtf8("Kafedra_cancelB"));

        horizontalLayout_7->addWidget(Kafedra_cancelB);


        verticalLayout_19->addLayout(horizontalLayout_7);

        tabWidget->addTab(Kafedra, QString());
        Forma_obucheniya = new QWidget();
        Forma_obucheniya->setObjectName(QString::fromUtf8("Forma_obucheniya"));
        verticalLayout_20 = new QVBoxLayout(Forma_obucheniya);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_13 = new QLabel(Forma_obucheniya);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_13);

        Forma = new QTableView(Forma_obucheniya);
        Forma->setObjectName(QString::fromUtf8("Forma"));

        verticalLayout_13->addWidget(Forma);


        verticalLayout_20->addLayout(verticalLayout_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        Forma_addB = new QPushButton(Forma_obucheniya);
        Forma_addB->setObjectName(QString::fromUtf8("Forma_addB"));

        horizontalLayout_8->addWidget(Forma_addB);

        Forma_deleteB = new QPushButton(Forma_obucheniya);
        Forma_deleteB->setObjectName(QString::fromUtf8("Forma_deleteB"));

        horizontalLayout_8->addWidget(Forma_deleteB);

        Forma_acceptB = new QPushButton(Forma_obucheniya);
        Forma_acceptB->setObjectName(QString::fromUtf8("Forma_acceptB"));

        horizontalLayout_8->addWidget(Forma_acceptB);

        Forma_cancelB = new QPushButton(Forma_obucheniya);
        Forma_cancelB->setObjectName(QString::fromUtf8("Forma_cancelB"));

        horizontalLayout_8->addWidget(Forma_cancelB);


        verticalLayout_20->addLayout(horizontalLayout_8);

        tabWidget->addTab(Forma_obucheniya, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1304, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        Plan_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Plan_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Plan_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Plan_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Plan), QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        Status_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Status_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Status_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Status_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Status), QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\204\320\265\320\264\321\200\320\260", nullptr));
        Specialnost_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Specialnost_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Specialnost_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Specialnost_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Specialnost), QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        Spez_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Spez_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Spez_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Spez_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Spez), QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275", nullptr));
        Potok_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Potok_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Potok_acceptB_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Potok_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Potok), QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\204\320\265\320\264\321\200\320\260", nullptr));
        Kafedra_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Kafedra_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Kafedra_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Kafedra_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Kafedra), QCoreApplication::translate("MainWindow", "\320\232\320\260\321\204\320\265\320\264\321\200\320\260", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        Forma_addB->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Forma_deleteB->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Forma_acceptB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Forma_cancelB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Forma_obucheniya), QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
