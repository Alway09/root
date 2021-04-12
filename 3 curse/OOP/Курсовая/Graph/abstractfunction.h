#ifndef ABSTRACTFUNCTION_H
#define ABSTRACTFUNCTION_H

#include <cmath>
#include <QString>
#include <QPair>

class AbstractFunction
{
public:
    AbstractFunction(){};
    virtual ~AbstractFunction(){};

    virtual QPair<double, double> getValue(double arg) const = 0;
    virtual QString getName() const = 0;
};







class infinity_exeption
{
public:
    infinity_exeption(){};
    ~infinity_exeption(){};

    QString getError(){
        return "В диапазон аргумента входит значение, функция от которого бесконечна!";
    }
};

class borders_exeption
{
public:
    borders_exeption(){};
    ~borders_exeption(){};

    QString getError(){
        return "Заданный диапазон аргумента не соответствует графику!";
    }
};

#endif // ABSTRACTFUNCTION_H
