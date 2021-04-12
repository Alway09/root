#ifndef CARTESIANFUNCTIONS_H
#define CARTESIANFUNCTIONS_H

#include "abstractfunction.h"

class f_sin : public AbstractFunction
{
public:
    f_sin() : AbstractFunction(){};
    ~f_sin(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(arg, sin(arg));
    };

    QString getName() const override final{
        return "y = sin(x)";
    }
};

class f_cos : public AbstractFunction
{
public:
    f_cos() : AbstractFunction(){};
    ~f_cos(){};

    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(arg, cos(arg));
    }

    QString getName() const override final{
        return "y = cos(x)";
    }
};

class f_tg : public AbstractFunction
{
public:
    f_tg() : AbstractFunction(){};
    ~f_tg(){};

    QPair<double, double> getValue(double arg) const override final{
        if(arg <= -M_PI/2 || arg >= M_PI/2){
            throw infinity_exeption();
        }

        return QPair<double, double>(arg, sin(arg)/cos(arg));
    }

    QString getName() const override final{
        return "y = tg(x)";
    }
};

class f_giperbola1 : public AbstractFunction
{
public:
    f_giperbola1() : AbstractFunction(){};
    ~f_giperbola1(){};

    QPair<double, double> getValue(double arg) const override final{
        if(arg >= 0){
            throw borders_exeption();
        }

        return QPair<double, double>(arg, 1/arg);
    }

    QString getName() const override final{
        return "y = 1/x (x<0)";
    }
};

class f_giperbola2 : public AbstractFunction
{
public:
    f_giperbola2() : AbstractFunction(){};
    ~f_giperbola2(){};

    QPair<double, double> getValue(double arg) const override final{
        if(arg <= 0){
            throw borders_exeption();
        }

        return QPair<double, double>(arg, 1/arg);
    }

    QString getName() const override final{
        return "y = 1/x (x>0)";
    }
};

class f_square_root : public AbstractFunction
{
public:
    f_square_root() : AbstractFunction(){};
    ~f_square_root(){};

    QPair<double, double> getValue(double arg) const override final{
        if(arg < 0){
            throw borders_exeption();
        }

        return QPair<double, double>(arg, sqrt(arg));
    }

    QString getName() const override final{
        return "y = sqrt(x)";
    }
};

class f_parabola : public AbstractFunction
{
public:
    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(arg, arg*arg);
    }

    QString getName() const override final{
        return "y = x^2";
    }
};

class f_cube_parabola : public AbstractFunction
{
public:
    QPair<double, double> getValue(double arg) const override final{
        return QPair<double, double>(arg, arg*arg*arg);
    }

    QString getName() const override final{
        return "y = x^3";
    }
};

#endif // CARTESIANFUNCTIONS_H
