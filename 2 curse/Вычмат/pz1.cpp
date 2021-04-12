#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;

float f(float x){
    float y = (2.0*cos(5.0*x)/3.0)-(x/6.0)+(1.0/3.0);
    return y;
}

float canon(float x){
    float y = x - f(x) * (1.0/2.36) * (-1);
    return y;
}

float p(float x){
    double y = (1.0/sqrt(1.0-pow((x/4.0-1.0/2), 2))) * (-1.0/20.0);
    return y;
}

float firstDerivative(float x){
    float y = (-10.0*sin(5.0*x)/3.0)-(1.0/6.0);
    return y;
}

float secondDerivative(float x){
    float y = (-50.0*cos(5.0*x)/3.0);
}

float m1(float E, float lg, float rg){
    float c = (lg+rg)/2.0;
    int iter = 0;
    cout << "x(0) = " << c << "\n";

    while(abs(c-lg) > E){
        iter++;
        if(f(c)*f(lg) > 0){
            lg = c;
            c = (lg+rg)/2.0;
        } else{
            rg = c;
            c = (lg+rg)/2.0;
        }
        cout << "x(" << iter << ") = " << c << "\n";
    }

    cout << "\nКоличество итераций: " << iter << "\n";

    return c;
}

float m2(float E, float a, float b){
    float d, c;
    int iter = 0;
    cout << "x(0) = " << (a+b)/2.0 << "\n";

    while(abs(b-a) > E){
        iter++;
        if(firstDerivative(a)*secondDerivative(a) > 0){
            c = a - f(a)*(b-a)/(f(b)-f(a));
            d = -1*f(a)/firstDerivative(a)+a;
            a = d; b = c;
        } else{
            c = a - f(a)*(b-a)/(f(b)-f(a));
            d = b-(f(b)/firstDerivative(b));
            a = c; b = d;
        }
        cout << "x(" << iter << ") = " << (a+b)/2.0 << "\n";
    }

    cout << "\nКоличество итераций: " << iter << "\n";

    return (a+b)/2.0;
}

float m3(float E, float a, float b){
    float x = (a+b)/2.0;
    int iter = 0;
    cout << "x(0) = " << x << "\n";

    while(abs(canon(x) - x) >= E){
        iter++;
        x = canon(x);
        cout << "x(" << iter << ") = " << x << "\n";
    }

    cout << "\nКоличество итераций: " << iter << "\n";

    return x;
}

void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

int main(int argc, char* argv[]){
    const float E = pow(10, -5);
    float g[] = {1.4, 1.8};
    int ans;
    float r;
    bool flag = true;

    while(flag){
        clearScreen();

        cout << "Уравнение: (2*cos(5*x)/3)-(x/6)+(1/3) = 0\n";
        cout << "1. Метод половинного деления\n";
        cout << "2. Метод хорд и касательных\n";
        cout << "3. Метод простых итераций\n";
        cout << "0. Выход\n\n";
        cout << "   >";
        cin >> ans;

        switch(ans){
            case 1:
                clearScreen();
                cout << "Метод половинного деления\n\n";
                cout << "a = " << g[0] << " b = " << g[1] << "\n\n";
                r = m1(E, g[0], g[1]);
                cout << "\nКорень: " << r << "  Значение функции: " << f(r) << "\n\n";
                cout << "Введите любую цифру... ";
                cin >> ans;
                break;
            case 2:
                clearScreen();
                cout << "Метод половинного хорд и кастельных\n\n";
                cout << "a = " << g[0] << " b = " << g[1] << "\n\n";
                r = m2(E, g[0], g[1]);
                cout << "\nКорень: " << r << "  Значение функции: " << f(r) << "\n\n";
                cout << "Введите любую цифру... ";
                cin >> ans;
                break;
            case 3:
                clearScreen();
                cout << "Метод простых итераций\n\n";
                cout << "a = " << g[0] << " b = " << g[1] << "\n\n";
                r = m3(E, g[0], g[1]);
                cout << "\nКорень: " << r << "  Значение функции: " << f(r) << "\n\n";
                cout << "Введите любую цифру... ";
                cin >> ans;
                break;
            case 0:
                flag = false;
                break;
            default:
                break;
        }
    }

    clearScreen();

    return 0;
}
