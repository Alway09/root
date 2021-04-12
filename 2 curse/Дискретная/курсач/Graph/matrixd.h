#ifndef MATRIXD_H
#define MATRIXD_H

#include<QVector>
#include<QPair>
#include<QString>

class MatrixD
{
public:
    MatrixD(QVector<QVector<QPair<int, QString>>>, QVector<int>, QVector<int>);
    int sum_of_const();
    void out() const;
    void reduction(int, int);
    void inf_return_trip();
    void add_inf(int, int);
    QPair<int,int> edge();
    size_t get_matrix_size() const;
    void add_to_path(QPair<int,int>);
    void set_bottomLimit(int);
    int get_bottomLimit() const;
    int get_str_num(int) const;
    int get_col_num(int) const;
    QPair<int,QString> get_data(int, int) const;
    void set_data(int, int, int);
    void set_data(int, int, QString);
    QVector<QPair<int,int>> get_path() const;
    void last_transform(int);
    bool check_path_right() const;
    bool all_inf() const;

private:
    QVector<QVector<QPair<int, QString>>> matrix;
    QVector<int> table_s;
    QVector<int> table_c;
    QVector<QPair<int,int>> path;
    int bottomLimit;
};

#endif // MATRIXD_H
