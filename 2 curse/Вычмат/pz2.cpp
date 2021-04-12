#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

float* multM(float* M[], float* V, int N){ // Умножение матрицы на вектор
    float* buf = new float[N];
    for(int i = 0; i < N; i++){
        buf[i] = 0;
    }

    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            buf[i] += M[i][j] * V[j];
        }
    }

    return buf;
}

float* sumM(float* V1, float* V2, int N){
    float* buf = new float[N];
    for(int i = 0 ; i < N; i++){
        buf[i] = V1[i] + V2[i];
    }
    return buf;
}

float* sumM(float* V1, float* V2, float* V3, int N){
    float* buf = new float[N];
    for(int i = 0 ; i < N; i++){
        buf[i] = V1[i] + V2[i] + V3[i];
    }
    return buf;
}

float norma(float* V1, float* V2, int N){ // Норма двух векторов
    float res = 0;
    for(int i = 0; i < N; i++){
        res += abs(V1[i] - V2[i]);
    }
    return res;
}

void m1(float* C[], float* d, int N){
    float* x_k = new float[N];
    for(int i = 0; i < N; i++){
        x_k[i] = d[i];
    }
    float* x_k1 = new float[N];
    x_k1 = x_k;
    int k = 0; float E = 0.00001;

    cout << k+1 << ": ";
    for(int i = 0; i < N; i++){
        cout << "x" << i+1 << "=" << x_k1[i] << " ";
    }cout << "\n";
    k++;

    do{
        x_k = x_k1;
        x_k1 = sumM(multM(C, x_k, N), d, N);
        cout << k+1 << ": ";
        for(int i = 0; i < N; i++){
            cout << "x" << i+1 << "=" << x_k1[i] << " ";
        }cout << "\n";
        k++;
    } while(norma(x_k, x_k1, N) > E);

    cout << "\n\n   Ответ:\n   ";
    for(int i = 0 ; i < N; i++){
        cout << "x" << i+1  << "=" << x_k1[i] << " ";
    }cout << "\n";
}

void m2(float* C[], float* d, int N){
    float** L = new float*[N];
    float** U = new float*[N];
    for(int i = 0; i < N; i++){
        L[i] = new float[N];
        U[i] = new float[N];
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j >= i){
                U[i][j] = C[i][j];
                L[i][j] = 0;
            } else{
                L[i][j] = C[i][j];
                U[i][j] = 0;
            }
        }
    }

    float* x_k = new float[N];
    for(int i = 0; i < N; i++){
        x_k[i] = d[i];
    }
    float* x_k1 = new float[N];
    int k = 0; float E = 0.00001;

    cout << k+1 << ": ";
    for(int i = 0; i < N; i++){
        cout << "x" << i+1 << "=" << x_k[i] << " ";
    }cout << "\n";
    k++;

    do{
        x_k = x_k1;
        x_k1 = sumM(multM(C, x_k, N), d, N);
        x_k1 = sumM(multM(L, x_k1, N), multM(U, x_k, N), d, N);
        cout << k+1 << ": ";
        for(int i = 0; i < N; i++){
            cout << "x" << i+1 << "=" << x_k1[i] << " ";
        }cout << "\n";
        k++;
    }while(norma(x_k, x_k1, N) > E);

    cout << "\n\n   Ответ:\n   ";
    for(int i = 0 ; i < N; i++){
        cout << "x" << i+1  << "=" << x_k1[i] << " ";
    }cout << "\n";
}

void cls(){
    cout << "\033[2J\033[1;1H";
}

int main(){
    //-------------------------------- Чтение основной матрицы из файла
    int N;
    ifstream file ("matrix.txt");
    if(!file){
        cout << "File is not open!\n";
        return -1;
    }

    file >> N;
    float** A = new float*[N];
    for(int i = 0; i < N; i++){
        A[i] = new float[N];
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            file >> A[i][j];
        }
    }

    float* b = new float[N];

    for(int i = 0; i < N; i++){
        file >> b[i];
    }

    file.close();
    //-------------------------------- Преобразование
    float** C = new float*[N];
    for(int i = 0; i < N; i++){
        C[i] = new float[N];
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == j){
                C[i][j] = 0;
            } else{
                C[i][j] = -A[i][j]/A[i][i];
            }
        }
    }

    float* d = new float[N];
    for(int i = 0; i < N; i++){
        d[i] = b[i]/A[i][i];
    }
    //--------------------------------

    int ans;
    bool flag = true;
    while(flag){
        cls();
        cout << "Исходная система: \n";
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout << A[i][j] << "x" << j+1 << " + ";
            }
            cout << "= " << b[i] << "\n";
        }cout << "\n\n";

        cout << "1. Метод простых итераций\n";
        cout << "2. Метод Зейделя\n";
        cout << "0. Выход\n\n    >";
        cin >> ans;

        switch(ans){
            case 1:
                cls();
                cout << "Метод простых итераций\n\n";
                m1(C, d, N);
                cout << "\nВведите любую цифру... ";
                cin >> ans;
                break;
            case 2:
                cls();
                cout << "Метод Зейделя\n\n";
                m2(C, d, N);
                cout << "\nВведите любую цифру... ";
                cin >> ans;
                break;
            case 0:
                flag = false;
                break;
            default:
                break;
        }
    }

    cls();
    return 0;
}