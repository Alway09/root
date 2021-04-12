#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

void showTree(int mass[], int root, int razm, int n_lvl);

int main(){
    int n, ans;
    int razm = 2; // Переменная для размера масссива элементов бинарного дерева
    bool flag = true;
    srand((unsigned int)time(NULL));

m:  cout << "Введите высоту дерева: ";
    cin >> n;

    for(int i = 0; i < n-1; i++){
        razm *= 2;
    }
    razm--;

     int* mass = new int [razm];

    for(int i = 0; i < razm; i++){
        mass[i] = rand()%100;
        //mass[i] = i;
    }

    while(flag){
        cout << "\033[2J\033[1;1H";
        cout << "Введенная высота дерева: " << n << "\n";
        cout << " 1. Вывести бинарное дерево на экран\n";
        cout << " 2. Вывести бинарное дерево и массив сыновей этого бинарного дерева на экран\n";
        cout << " 3. Задать другую рамерность дерева\n\n";
        cout << " 0. Выйти из программы\n\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            cout << "-" << mass[0] << "\n";
            showTree(mass, 0, razm, n);

            cout << "\nДля продолжения введите любую цифру... ";
            cin >> ans;
            break;

        case 2:
            for(int i = 0; i < razm; i++){
                cout << mass[i] << " ";
            }; cout << "\n";

            cout << "-" << mass[0] << "\n";
            showTree(mass, 0, razm, n);

            cout << "\nДля продолжения введите любую цифру... ";
            cin >> ans;
            break;

        case 3:
            cout << "\033[2J\033[1;1H";
            razm = 2;
            goto m;
            break;

        case 0:
            flag = false;
            break;
        
        default:
            break;
        }
    }

    return 0;
}

void showTree(int mass[], int root, int razm, int n_lvl){ // Процедура вывода дерева на экран
    int n = 0;
    if(2*root + 1 < razm){
        n = 2*root + 1;
        cout << setw(3*(n+n_lvl)/n_lvl) <<  "L-" << mass[n] << "(" << mass[root] << ")" << "\n";
        showTree(mass, n, razm, n_lvl);
    }
    if(2*root + 2 < razm){
        n = 2*root + 2;
        cout << setw(3*(n+n_lvl)/n_lvl - 1) << "R-" << mass[n] << "(" << mass[root] << ")" << "\n";
        showTree(mass, n, razm, n_lvl);
    }
}