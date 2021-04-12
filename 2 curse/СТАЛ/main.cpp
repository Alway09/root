#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//-----------------------------------------

int main(){
    int ind_sons, root, razm = 2;

    int mass[] = {12,5,8,4,20,3,1,6,7};
    int tree[31];
    razm = 31;

    for(int i = 0 ; i < razm; i++){
        tree[i] = -1;
    }
    tree[0] = mass[0];
    

    for(int i = 1; i < 9; i++){
        ind_sons = 0;
        root = mass[0];
        while(1){
            if(mass[i] > root){
                if(tree[2*ind_sons+2] == -1){
                    tree[2*ind_sons+2] = mass[i];
                    break;
                } else{
                    root = tree[2*ind_sons+2];
                    ind_sons = 2*ind_sons + 2;
                }
            } else{
                if(tree[2*ind_sons+1] == -1){
                    tree[2*ind_sons+1] = mass[i];
                    break;
                } else{
                    root = tree[2*ind_sons+1];
                    ind_sons = 2*ind_sons + 1;
                }
            }
        }
    }

    for(int i = 0; i < razm; i++){
        cout << tree[i] << " ";
    } cout << "\n";
}