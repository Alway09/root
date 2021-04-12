#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
int am = 0;

int* createBinaryScale(char* U, char* P, int N){
    int* Pb = new int[N];
    int cout = 0;

    for(int i = 0; i < N; i++){
        if(P[cout] == U[i]){
            Pb[i] = 1;
            cout++;
        } else Pb[i] = 0;
    }

    return Pb;
}

int* createBinaryScale(char* U, char E, int N){
    int* Eb = new int[N];

    for(int i = 0; i < N; i++){
        if(E == U[i]){
            Eb[i] = 1;
        } else Eb[i] = 0;
    }

    return Eb;
}

int* combination(int* P1, int* P2, int N){
    int* P3 = new int[N];

    for(int i = 0; i < N; i++){
        if(P1[i] | P2[i]){
            P3[i] = 1;
        } else P3[i] = 0;
    }

    return P3;
}

int* crossing(int* P1, int* P2, int N){
    int* P3 = new int[N];

    for(int i = 0; i < N; i++){
        if(P1[i] & P2[i]){
            P3[i] = 1;
        } else P3[i] = 0;
    }

    return P3;
}

int* addition(int* P1, int N){
    int* P3 = new int[N];

    for(int i = 0; i < N; i++){
        if(P1[i]){
            P3[i] = 0;
        } else P3[i] = 1;
    }

    return P3;
}

int* difference(int* P1, int* P2, int N){
    int* P3 = crossing(P1, addition(P2, N), N);

    return P3;
}

bool check(char E, int* Pb, char* U, int N){
    int* Eb = createBinaryScale(U, E, N);

    for(int i = 0; i < N; i++){
        if(Eb[i] & Pb[i]){
            return true;
        }
    }

    return false;
}

char* convert(char* U, int* Pb, int N){
    char* M = new char[N+1];
    //int cout = 0;

    for(int i = 0; i < N; i++){
        if(Pb[i]){
            M[am] = U[i];
            am++;
        }
    }
    M[am] = '\0';

    return M;
}

int main(){
    string U, A, B, C;

    ifstream file ("text.txt");
    if(!file){
        cout << "File is not open!\n";
        return -1;
    } else {
        file >> U >> A >> B >> C;
    }
    file. close();

    int N = U.length(); char Uc[N+1]; strcpy(Uc, U.c_str());
    char Ac[A.length()+1]; strcpy(Ac, A.c_str()); int* Ab = createBinaryScale(Uc, Ac, N);
    char Bc[B.length()+1]; strcpy(Bc, B.c_str()); int* Bb = createBinaryScale(Uc, Bc, N);
    char Cc[C.length()+1]; strcpy(Cc, C.c_str()); int* Cb = createBinaryScale(Uc, Cc, N);

    cout << "~((A п B) / ~C)\n";

    cout << "U = {";
    for(int i = 0; i < N; i++){
        cout << Uc[i];
        if(i < N-1){
            cout << ", ";
        }
    } cout << "}\n";

    cout << "A = {";
    for(int i = 0; i < A.length(); i++){
        cout << Ac[i];
        if(i < A.length()-1){
            cout << ", ";
        }
    } cout << "}                                     Binary scale: ";
    for(int i = 0 ; i < N; i++){
        cout << Ab[i];
    } cout << "\n";

    cout << "B = {";
    for(int i = 0; i < B.length(); i++){
        cout << Bc[i];
        if(i < B.length()-1){
            cout << ", ";
        }
    } cout << "}                               Binary scale: ";
    for(int i = 0 ; i < N; i++){
        cout << Bb[i];
    } cout << "\n";

    cout << "C = {";
    for(int i = 0; i < C.length(); i++){
        cout << Cc[i];
        if(i < C.length()-1){
            cout << ", ";
        }
    } cout << "}                            Binary scale: ";
    for(int i = 0 ; i < N; i++){
        cout << Cb[i];
    } cout << "\n\n";

    cout << "1. ~C = {";
    int *Fb = addition(Cb, N);
    char* M = convert(Uc, Fb, N);
    for(int i = 0; i  < am; i++){
        cout << M[i];
        if(i < am-1){
            cout << ", ";
        }
    } cout << "}                              Binary scale: ";
    for(int i = 0; i < N; i++){
        cout << Fb[i];
    } cout << "\n";
    am = 0;

    cout << "2. A u B = {";
    int* Db = combination(Ab, Bb, N);
    M = convert(Uc, Db, N);
    for(int i = 0; i  < am; i++){
        cout << M[i];
        if(i < am-1){
            cout << ", ";
        }
    } cout << "}                     Binary scale: ";
    for(int i = 0; i < N; i++){
        cout << Db[i];
    } cout << "\n";
    am = 0;

    cout << "3. (A п B) / ~C = {";
    int* Zb = difference(Db, Fb, N);
    M = convert(Uc, Zb, N);
    for(int i = 0; i  < am; i++){
        cout << M[i];
        if(i < am-1){
            cout << ", ";
        }
    } cout << "}                          Binary scale: ";
    for(int i = 0; i < N; i++){
        cout << Zb[i];
    } cout << "\n";
    am = 0;

    cout << "4. ~((A п B) / ~C) = {";
    Fb = addition(Zb, N);
    M = convert(Uc, Fb, N);
    for(int i = 0; i  < am; i++){
        cout << M[i];
        if(i < am-1){
            cout << ", ";
        }
    } cout << "}     Binary scale: ";
    for(int i = 0; i < N; i++){
        cout << Fb[i];
    } cout << "\n";
    am = 0;

    getchar();

    return 0;
}