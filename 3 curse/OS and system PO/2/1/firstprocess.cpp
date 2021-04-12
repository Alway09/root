#include<iostream>
using namespace std;

int main(int argc, char *argv[]){
    
    cout << "    Hello, im first process programm! Arguments: ";

    for(int i = 0; i < argc; ++i){
        cout << argv[i] << " ";
    }
    cout << "\n";
    
    return 0;
}