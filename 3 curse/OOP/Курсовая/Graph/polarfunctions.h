#ifndef POLARFUNCTION_H
#define POLARFUNCTION_H

#include "abstractfunction.h"

class f_spiral_archimeda : public AbstractFunction
{
public:
    f_spiral_archimeda() : AbstractFunction(){};
    ~f_spiral_archimeda(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(arg*cos(arg), arg*sin(arg));
    };

    QString getName() const override final{
        return "r = ф";
    }
};

class f_cardioida : public AbstractFunction
{
public:
    f_cardioida() : AbstractFunction(){};
    ~f_cardioida(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(cos(arg) + pow(cos(arg), 2), sin(arg) + sin(arg)*cos(arg));
    };

    QString getName() const override final{
        return "r = 1 + cos(ф)";
    }
};

class f_polar_rose1 : public AbstractFunction
{
public:
    f_polar_rose1() : AbstractFunction(){};
    ~f_polar_rose1(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(sin(7*arg/4)*cos(arg), sin(7*arg/4)*sin(arg));
    };

    QString getName() const override final{
        return "r = sin(7*ф/4)";
    }
};

class f_polar_rose2 : public AbstractFunction
{
public:
    f_polar_rose2() : AbstractFunction(){};
    ~f_polar_rose2(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(sin(6*arg)*cos(arg), sin(6*arg)*sin(arg));
    };

    QString getName() const override final{
        return "r = sin(6*ф)";
    }
};

class f_leminiscate : public AbstractFunction
{
public:
    f_leminiscate() : AbstractFunction(){};
    ~f_leminiscate(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(cos(arg) * pow(cos(2*arg), 0.5), sin(arg) * pow(cos(2*arg), 0.5));
    };

    QString getName() const override final{
        return "r = (cos(2ф))^0.5";
    }
};

class f_pascal_snail : public AbstractFunction
{
public:
    f_pascal_snail() : AbstractFunction(){};
    ~f_pascal_snail(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(2*cos(arg) - 4*sin(arg)*cos(arg), 2*sin(arg) - 4*pow(sin(arg), 2));
    };

    QString getName() const override final{
        return "r = 2 - 4sin(ф)";
    }
};

class f_butterfly : public AbstractFunction
{
public:
    f_butterfly() : AbstractFunction(){};
    ~f_butterfly(){};

    QPair<double, double> getValue(double arg) const override final{
        double r(exp(sin(arg)) - 2*cos(4*arg) + pow(sin((2*arg)/24), 5));

        return QPair<double, double>(r*cos(arg), r*sin(arg));
    };

    QString getName() const override final{
        return "r = exp(sin(ф)) - 2cos(4ф) + sin^5((2ф - PI)/24)";
    }
};

class f_heart : public AbstractFunction
{
public:
    f_heart() : AbstractFunction(){};
    ~f_heart(){};

    QPair<double, double> getValue(double arg) const override final{
        double r(2 - 2*sin(arg) + sin(arg)*(sqrt(abs(cos(arg))))/(sin(arg)+1.4));

        return QPair<double, double>(r*cos(arg), r*sin(arg));
    };

    QString getName() const override final{
        return "r = 2 - 2sin(ф) + sin(ф)(sqtr(abs(cos(ф))) / (sin(ф)+1.4))";
    }
};

#endif // POLARFUNCTION_H
