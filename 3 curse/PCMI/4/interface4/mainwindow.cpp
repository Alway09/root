#include "mainwindow.h"
#include "ui_mainwindow.h"

static const std::string filename("../logs.txt");

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), t(false)
{
    ui->setupUi(this);
    initCB();

    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCB()
{
    if(experiment == 1 || experiment == 5)
    {
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        ui->comboBox->clear();
        for (int i = 2; i <= 9; i++)
        {
            ui->comboBox->addItem(QString::number(i));
        }
    }
    else if (experiment == 2)
    {
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        ui->comboBox->clear();
        for (int i = 3; i <= 6; i++)
        {
            ui->comboBox->addItem(QString::number(i));
        }
    }
    else if (experiment == 3)
    {
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        ui->comboBox->clear();
        for (int i = 6; i <= 12; i++)
        {
            ui->comboBox->addItem(QString::number(i));
        }
    }
    else if (experiment == 4)
    {
        ui->comboBox->clear();
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        for (int i = 7; i <= 18; i++)
        {
            ui->comboBox->addItem(QString::number(i));
        }
    }

    if (experiment == 5)
    {
        ui->comboBox_3->addItems({"70%", "80%", "90%", "100%", "110%"});
        ui->comboBox_4->addItems({"Нормальный", "Полужирный", "Курсив", "Подчеркнутый"});
    }
    else
    {
        ui->comboBox_3->addItem("100%");
        ui->comboBox_4->addItem("Нормальный");
    }

    if (ui->comboBox_2->count() == 0)
    {
        ui->comboBox_2->addItem("Опыт 1");
        ui->comboBox_2->addItem("Опыт 2, 1 меню");
        ui->comboBox_2->addItem("Опыт 2, 2 меню");
        ui->comboBox_2->addItem("Опыт 2, 3 меню");
        ui->comboBox_2->addItem("Опыт 3");
    }
}

void MainWindow::changeCountPanels()
{
    if (experiment == 1 || experiment == 2 || experiment == 5)
    {
        ui->groupBox_2->show();
        ui->groupBox_3->hide();
        ui->groupBox_4->hide();

        QList<QPushButton*> panels = ui->groupBox_2->findChildren<QPushButton*>();

        for (int i = 0; i < panels.size(); i++)
        {
            panels[i]->hide();
        }

        for (int i = 0; i < countPanels; i++)
        {
            panels[i]->show();
        }
    }
    else if (experiment == 3)
    {
        ui->groupBox_2->show();
        ui->groupBox_3->show();
        ui->groupBox_4->hide();

        QList<QPushButton*> panels1 = ui->groupBox_2->findChildren<QPushButton*>();

        QList<QPushButton*> panels2 = ui->groupBox_3->findChildren<QPushButton*>();

        for (int i = 0; i < panels1.size(); i++)
        {
            panels1[i]->hide();
        }
        for (int i = 0; i < panels2.size(); i++)
        {
            panels2[i]->hide();
        }

        for (int i = 0; i < countPanels/2; i++)
        {
            panels1[i]->show();
        }

        for (int i = 0; i < countPanels/2 + countPanels%2; i++)
        {
            panels2[i]->show();
        }
    }
    else if (experiment == 4)
    {
        ui->groupBox_2->show();
        ui->groupBox_3->show();
        ui->groupBox_4->show();

        QList<QPushButton*> panels1 = ui->groupBox_2->findChildren<QPushButton*>();

        QList<QPushButton*> panels2 = ui->groupBox_3->findChildren<QPushButton*>();

        QList<QPushButton*> panels3 = ui->groupBox_4->findChildren<QPushButton*>();

        for (int i = 0; i < panels1.size(); i++)
        {
            panels1[i]->hide();
        }
        for (int i = 0; i < panels2.size(); i++)
        {
            panels2[i]->hide();
        }
        for (int i = 0; i < panels3.size(); i++)
        {
            panels3[i]->hide();
        }

        for (int i = 0; i < countPanels/3; i++)
        {
            panels1[i]->show();
        }

        for (int i = 0; i < countPanels/3 + countPanels%3/2; i++)
        {
            panels2[i]->show();
        }

        if (countPanels%3 == 1)
        {
            for (int i = 0; i < countPanels/3 + countPanels%3/2 + 1; i++)
            {
                panels3[i]->show();
            }
        }
        else for (int i = 0; i < countPanels/3 + countPanels%3/2; i++)
        {
            panels3[i]->show();
        }

    }
}

void MainWindow::PanelClicked()
{
    numberClick++;
    int det = timer.elapsed() - timeStart;
    average += det;

    saveLog(det);
    StopTest();
    if (numberClick == 5)
    {
        ui->nextButton->setText("Начать");
        average /= numberClick;
        numberClick = 0;
        QString seconds = QString::number(average / 1000);
        QString mseconds = QString::number(average % 1000);
        if (mseconds.size() == 2)
        {
            mseconds = "0" + mseconds;
        }
        else if (mseconds.size() == 1)
        {
            mseconds = "00" + mseconds;
        }
        FILE* f = fopen(filename.c_str(), "a");
        fprintf(f, "average: %s,%s с\n\n", seconds.toStdString().c_str(), mseconds.toStdString().c_str());
        fclose(f);
        average = 0;
    }
}

void MainWindow::saveLog(int det)
{
    QString seconds = QString::number(det / 1000);
    QString mseconds = QString::number(det % 1000);
    if (mseconds.size() == 2)
    {
        mseconds = "0" + mseconds;
    }
    else if (mseconds.size() == 1)
    {
        mseconds = "00" + mseconds;
    }

    FILE* f = fopen(filename.c_str(), "a");
    fprintf(f, "№%d, n: %d, размер: %s, начертание: %s, t: %s,%s с\n", experiment, countPanels, ui->comboBox_3->currentText().toStdString().c_str(), ui->comboBox_4->currentText().toStdString().c_str(), seconds.toStdString().c_str(), mseconds.toStdString().c_str());
    fclose(f);

}

QList<QString> MainWindow::randomPanels()
{

    QList<QString> numbers;
    for (int i = 1; i <= countPanels; i++)
    {
        numbers.append(QString::number(i));
    }

    QList<QString> randomNumbers;
    while (numbers.size() > 0)
    {
        srand(time(nullptr));
        int ind = 0 + rand()%(numbers.size());
        randomNumbers.append(numbers[ind]);
        numbers.removeAt(ind);
    }
    return randomNumbers;


}

void MainWindow::addTextToPanels()
{
    QList<QGroupBox*> boxes = this->findChildren<QGroupBox*>();
    QList<QString> numbers = randomPanels();
    for (int i = 0; i < boxes.size(); i++)
    {
        if (!boxes[i]->isHidden() && boxes[i]->objectName() != "groupBox")
        {
            QList<QPushButton*> panels = boxes[i]->findChildren<QPushButton*>();

            for (int i = 0; i < panels.size(); i++)
            {
                if ((!panels[i]->isHidden()))
                {
                    panels[i]->setText(numbers[0]);
                    if (ui->label_2->text() == panels[i]->text() && experiment == 5)
                    {
                        panels[i]->setMinimumWidth(panels[i]->minimumWidth() * k);
                        panels[i]->setMaximumWidth(panels[i]->maximumWidth() * k);
                        QFont font = panels[i]->font();
                        font.setBold(bold);
                        font.setItalic(italic);
                        font.setUnderline(line);
                        panels[i]->setFont(font);
                    }
                    numbers.removeAt(0);
                }
            }
        }
    }
}

void MainWindow::removePanelText()
{
    QList<QPushButton*> panels = this->findChildren<QPushButton*>();
    for (int i = 0; i < panels.size(); i++)
    {
        if ((panels[i]->objectName() == "nextButton") || (panels[i]->objectName() == "cancelButton"))
        {
            panels.removeAt(i);
            i--;
        }
    }

    for (int i = 0; i < panels.size(); i++)
    {
        if ((!panels[i]->isHidden()))
        {
            if (ui->label_2->text() == panels[i]->text() && experiment == 5)
            {
                panels[i]->setMinimumWidth(panels[i]->minimumWidth() * 1/k);
                panels[i]->setMaximumWidth(panels[i]->maximumWidth() * 1/k);
                QFont font = panels[i]->font();
                font.setBold(false);
                font.setItalic(false);
                font.setUnderline(false);
                panels[i]->setFont(font);
            }
            panels[i]->setText("");

        }
    }
}

void MainWindow::StartTest()
{
    if (numberClick == 0) ui->nextButton->setText("Далее");
    t = true;

    srand(time(nullptr) + 17001%rand());
    ui->label_2->setText(QString::number((1 + rand()%countPanels)));
    if (experiment == 5) ui->label_2->hide();

    addTextToPanels();


    timeStart = timer.elapsed();

    moveCursor();

    qDebug() << ui->label_2->text() << endl;
}

void MainWindow::moveCursor()
{
    int X = geometry().x() + 480;
    int Y = geometry().y() + 275;

    cursor().setPos(X, Y);
}

void MainWindow::StopTest()
{
    t = false;

    removePanelText();

    ui->label_2->clear();
    if (experiment == 5) ui->label_2->show();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    countPanels = arg1.toInt();
    changeCountPanels();

}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    experiment = index + 1;
    initCB();
    changeCountPanels();

}

void MainWindow::on_nextButton_clicked()
{
    if (!t) StartTest();
}

void MainWindow::on_cancelButton_clicked()
{
    numberClick = 0;
    ui->nextButton->setText("Начать");
    QFont font = ui->nextButton->font();
    if (t) StopTest();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->label_2->text() == ui->pushButton_2->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->label_2->text() == ui->pushButton->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (ui->label_2->text() == ui->pushButton_3->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if (ui->label_2->text() == ui->pushButton_4->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->label_2->text() == ui->pushButton_5->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if (ui->label_2->text() == ui->pushButton_6->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if (ui->label_2->text() == ui->pushButton_7->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if (ui->label_2->text() == ui->pushButton_8->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if (ui->label_2->text() == ui->pushButton_9->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    if (ui->label_2->text() == ui->pushButton_19->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    if (ui->label_2->text() == ui->pushButton_20->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_21_clicked()
{
    if (ui->label_2->text() == ui->pushButton_21->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    if (ui->label_2->text() == ui->pushButton_22->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    if (ui->label_2->text() == ui->pushButton_23->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_24_clicked()
{
    if (ui->label_2->text() == ui->pushButton_24->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    if (ui->label_2->text() == ui->pushButton_25->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_26_clicked()
{
    if (ui->label_2->text() == ui->pushButton_26->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    if (ui->label_2->text() == ui->pushButton_27->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    if (ui->label_2->text() == ui->pushButton_28->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    if (ui->label_2->text() == ui->pushButton_29->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_30_clicked()
{
    if (ui->label_2->text() == ui->pushButton_30->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_31_clicked()
{
    if (ui->label_2->text() == ui->pushButton_31->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    if (ui->label_2->text() == ui->pushButton_32->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_33_clicked()
{
    if (ui->label_2->text() == ui->pushButton_33->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_34_clicked()
{
    if (ui->label_2->text() == ui->pushButton_34->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_35_clicked()
{
    if (ui->label_2->text() == ui->pushButton_35->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_pushButton_36_clicked()
{
    if (ui->label_2->text() == ui->pushButton_36->text())
    {
        PanelClicked();
    }
}

void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    if (arg1 == "70%")
        k = 0.7;
    else if (arg1 == "80%")
        k = 0.8;
    else if (arg1 == "90%")
        k = 0.9;
    else if (arg1 == "100%")
        k = 1;
    else if (arg1 == "110%")
        k = 1.1;
}

void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Полужирный") {bold = true; italic = false; line = false;}
    else if (arg1 == "Курсив") {bold = false; italic = true; line = false;}
    else if (arg1 == "Подчеркнутый") {bold = false; italic = false; line = true;}
    else if (arg1 == "Нормальный") {bold = false; italic = false; line = false;}
}
