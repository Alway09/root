#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iomanip>

using namespace std;

int getRand(int b){
    return rand()%b;
}

int main(int argc, char* argv[]){
    srand(time(0));
    
    int m = atoi(argv[1]), n = atoi(argv[2]);
    int N, i, j, r;
    int** S = new int*[n];
    for(i = 0; i < n; i++){
        S[i] = new int[n];
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            S[i][j] = 0;
        }
    }

    cout << "k" << setw(3) << "|" << setw(2) << "N" << setw(2) << "|" << setw(2) << "i" << setw(2) << "|" << setw(2) << "j" << setw(2) << "|" << setw(5) << "S" << setw(10) << "\n"; 
    cout << setfill('-') << setw(30) << "\n";
    for(int k = 0; k < m; k++){
        N = getRand(n*n);
        i = floor(N/n);
        j = (N - (i)*n);
        cout << setfill(' ')<< setw(2) << k << setw(2) << "|" << setw(2) << N << setw(2) << "|" << setw(2) << i+1 << setw(2) << "|" << setw(2) << j+1 << setw(2) << "|" << "\n";
        if((i == j) || (S[i][j] == 1)){
            m++;
        } else {
            S[i][j] = 1;
            S[j][i] = 1;
        }
        for(i = 0; i < n; i++){
            cout << setw(4) << "|" << setw(4) << "|" << setw(4) << "|" << setw(4) << "|" << setw(2);
            for(j = 0; j < n; j++){
                cout << S[i][j] << " ";
            }
            cout << "\n";
        }
        cout << setfill('-') << setw(30) << "\n";
    }

    return 0;
}