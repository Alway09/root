#ifndef NEWTON_H
#define NEWTON_H

#include <QDialog>

namespace Ui {
class Newton;
}

class Newton : public QDialog
{
    Q_OBJECT

public:
    explicit Newton(QWidget *parent = nullptr);
    ~Newton();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Newton *ui;
};

#endif // NEWTON_H
