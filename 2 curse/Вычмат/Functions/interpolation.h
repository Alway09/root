#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QDialog>

namespace Ui {
class Interpolation;
}

class Interpolation : public QDialog
{
    Q_OBJECT

public:
    explicit Interpolation(QWidget *parent = nullptr);
    ~Interpolation();

private slots:
    void on_pushButton_clicked();

    void on_generateButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Interpolation *ui;
};

#endif // INTERPOLATION_H
