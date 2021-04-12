#ifndef MNK_H
#define MNK_H

#include <QDialog>

namespace Ui {
class MNK;
}

class MNK : public QDialog
{
    Q_OBJECT

public:
    explicit MNK(QWidget *parent = nullptr);
    ~MNK();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonM_clicked();

private:
    Ui::MNK *ui;
};

#endif // MNK_H
