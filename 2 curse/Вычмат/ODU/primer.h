#ifndef PRIMER_H
#define PRIMER_H

#include <QDialog>

namespace Ui {
class Primer;
}

class Primer : public QDialog
{
    Q_OBJECT

public:
    explicit Primer(QWidget *parent = nullptr);
    ~Primer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Primer *ui;
};

#endif // PRIMER_H
