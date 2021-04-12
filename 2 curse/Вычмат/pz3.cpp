#include<iostream>
#include<cmath>
using namespace std;

float f1(float x, float y){
    return sin(x-1)/2+y-1.3;
}

float f2(float x, float y){
    return x-sin(y+1)-0.8;
}

float* minusF(float x, float y){
    float* buf = new float[2];
    buf[0] = -1*f2(x, y);
    buf[1] = -1*f1(x, y);
    return buf;
}

float** W(float x, float y){
    float** buf = new float*[2];
    for(int i = 0; i < 2; i++){
        buf[i] = new float[2];
    }

    buf[0][0] = 1;
    buf[0][1] = -cos(y+1);
    buf[1][0] = cos(x-1)/2;
    buf[1][1] = 1;

    return buf;
}

float** preobrC(float* A[]){
    float** C = new float*[2];
    for(int i = 0; i < 2; i++){
        C[i] = new float[2];
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(i == j){
                C[i][j] = 0;
            } else{
                C[i][j] = -A[i][j]/A[i][i];
            }
        }
    }
    return C;
}

float* preobrD(float* A[], float* b){
    float* d = new float[2];
    for(int i = 0; i < 2; i++){
        d[i] = b[i]/A[i][i];
    }
    return d;
}

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

float* zeydel(float* C[], float* d, int N){
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
    float E = 0.00001;

    do{
        x_k = x_k1;
        x_k1 = sumM(multM(C, x_k, N), d, N);
        x_k1 = sumM(multM(L, x_k1, N), multM(U, x_k, N), d, N);
    }while(norma(x_k, x_k1, N) > E);

    return x_k;
}

float norma2(float* V1, float* V2){
    float x1 = abs(V1[0]-V2[0]);
    float x2 = abs(V1[1]-V2[1]);
    if(x1>x2) {return x1;} else {return x2;};
}

void newton(float x0, float y0){
    float* x_k = new float[2];
    float* x_k1 = new float[2];
    float** buf1;
    float* buf2;
    x_k1[0] = x0; x_k1[1] = y0;
    float* deltax;
    float E = 0.0001;
    int k = 0;

    cout << k << ". " << x_k1[0] << " " << x_k1[1] << "\n"; k++;

    do{
        x_k = x_k1;
        buf1 = preobrC(W(x_k[0], x_k[1]));
        buf2 = preobrD(W(x_k[0], x_k[1]), minusF(x_k[0], x_k[1]));
        deltax = zeydel(buf1, buf2, 2);
        x_k1 = sumM(x_k, deltax, 2);
        cout << k << ". " << x_k1[0] << " " << x_k1[1] << "\n"; k++;
    } while(norma2(x_k1, x_k) > E);

    cout << "\n   Ответ: ";
    for(int i = 0; i < 2; i++){
        cout << x_k1[i] << " ";
    } cout << "\n";
}

int main(){
    system("clear");
    cout << "Заданная система уравнений: \n";
    cout << "sin(x-1)/2+y = 1.3\n";
    cout << "x-sin(y+1)   = 0.8\n\n\n";
    cout << "Решение методом Ньютона:\n";
    newton(1,1);

    return 0;
}