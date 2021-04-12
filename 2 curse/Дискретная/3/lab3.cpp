#include<iostream>
#include<cmath>
using namespace std;

unsigned int** tableForm(int n, unsigned int* f){
    int s = pow(2, n);

    unsigned int** table = new unsigned int*[2];
    for(int i = 0; i < 2; i++){
        table[i] = new unsigned int[s];
    }

    for(int i = 0; i < s; i++){
        table[0][i] = i;
    }
    for(int i = 0; i < s; i++){
        table[1][i] = f[i];
    }

    return table;
}

void sdnf(unsigned int* table[], int s, int n){
    unsigned int buf = 0;
    int end = s;
    unsigned int** copy = table;

    for(int j = 0; j < s; j++){
        if(copy[1][j] == 1){
            end = j;
        }
    }

    cout << "СДНФ(f) = ";
    for(int j = 0; j < s; j++){
        if(copy[1][j] == 1){
            for(int i = 0; i < n; i++){
                buf<<=1;
                buf = buf | (copy[0][j] & 1);
                copy[0][j] >>= 1;
            }
            cout << "(";
            for(int i = 0; i < n; i++){
                if(buf&1){
                    cout << "x" << i+1;
                    if(i < n-1) cout << " ^ ";
                    buf>>=1;
                } else{
                    cout << "~x" << i+1;
                    if(i < n-1) cout << " ^ ";
                    buf>>=1;
                }
            }
            cout << ")";
            if(j != end) cout << " + ";
            buf = 0;
        }
    }
    cout << "\n";  
}

void sknf(unsigned int* table[], int s, int n){
    unsigned int buf = 0;
    int end = s;
    unsigned int ** copy = table;

    for(int j = 0; j < s; j++){
        if(copy[1][j] == 0){
            end = j;
        }
    }

    cout << "СКНФ(f) = ";
    for(int j = 0; j < s; j++){
        if(copy[1][j] == 0){
            for(int i = 0; i < n; i++){
                buf<<=1;
                buf = buf | (copy[0][j] & 1);
                copy[0][j] >>= 1;
            }
            cout << "(";
            for(int i = 0; i < n; i++){
                if(buf&1){
                    cout << "~x" << i+1;
                    if(i < n-1) cout << " + ";
                    buf>>=1;
                } else{
                    cout << "x" << i+1;
                    if(i < n-1) cout << " + ";
                    buf>>=1;
                }
            }
            cout << ")";
            if(j != end) cout << " ^ ";
            buf = 0;
        }
    }
    cout << "\n";
}

int main(){
    int n;
    cout << "Введите количество переменных, от которых зависит функция: ";
    cin >> n;
    int k = pow(2, n);
    unsigned int* f = new unsigned int[k];
    cout << "Введите значения функции: ";
    for(int i = 0; i < k; i++){
        cin >> f[i];
    }

    unsigned int** table = new unsigned int*[2];
    for(int i = 0; i < 2; i++){
        table[i] = new unsigned int[k];
    }

    table = tableForm(n, f);

    sdnf(table, k, n);
    sknf(table, k, n);

    return 0;
}