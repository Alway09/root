#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

const int N = 16;

struct ELEM
{
    int num;
    int row;
    int col;

    ELEM *right;
    ELEM *down;
};

int matrixForm(ELEM *List_Row, ELEM *List_Col); // Чтение матрицы из файла
ELEM* findRow(ELEM *List_Row, int i); // Поиск строки по индексу
ELEM* findCol(ELEM *List_Col, int i); //Поиск колонки по индексу
ELEM* initRow(ELEM *List_Row, int i); //Создание списка строк
ELEM* initCol(ELEM *List_Col, int i); //Создание списка колонок
void showMatrix(ELEM *List_Row); // Вывод матрицы на экран
int getData(ELEM* List_Row, int i, int j); // Поиск значения элемента матрицы по индексу
int sum(ELEM* List_Row, int j); // Определение суммы элементов указанного столбца в нечетных строках


int main(){

    ELEM *List_Row = NULL;
    ELEM *List_Col = NULL;
    bool flag = true;
    int ans, i, j, num;

    for(int i = 0; i < N; i++){
        List_Col = initCol(List_Col, i);
        List_Row = initRow(List_Row, i);
    }

    matrixForm(List_Row, List_Col);

    while(flag){
        cout << "\033[2J\033[1;1H";
        cout << "1. Вывести матрицу на экран\n";
        cout << "2. Получить значение элемента по номеру строки и столбца\n";
        cout << "3. Определить суммы элементов указанного столбца в нечетных строках\n\n";
        cout << "0. Выйти из программы\n\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            cout << "\033[2J\033[1;1H";
            showMatrix(List_Row);
            cout << "\n\n Продолжить? (1-да, 2-нет)\n\n   >";
            cin >> ans;

            if(ans == 2){
                flag = false;
            }  
            break;

        case 2:
            cout << "\033[2J\033[1;1H";
            cout << "  Введите номер строки и номер столбца\n";
            cout << "Строка: ";
            cin >> i; 
            cout << "Столбец: ";
            cin >> j;

            if(i > N || i < 0 || j > N || j < 0){
                cout << "\n Такого элемента не существует!";
                goto m1;
            }

            cout << "\n\n   Ответ: " << getData(List_Row, i, j);

m1:         cout << "\n\n Продолжить? (1-да, 2-нет)\n\n   >";
            cin >> ans;

            if(ans == 2){
                flag = false;
            }
            break;

        case 3:
            cout << "\033[2J\033[1;1H";
            cout << "Введите номер столбца: ";
            cin >> num;

            if(num > N || num < 0){
                cout << "\n Такого столбца не существует!";
                goto m2;
            }

            cout << "Ответ: " << sum(List_Row, num);

m2:         cout << "\n\n Продолжить? (1-да, 2-нет)\n\n   >";
            cin >> ans;

            if(ans == 2){
                flag = false;
            }
            break;

        case 0:
            flag = false;
            break;
        
        default:
            break;
        }
    }

    cout << "\033[2J\033[1;1H";
    return 0;
}

int sum(ELEM* List_Row, int j){ // Определение суммы элементов указанного столбца в нечетных строках
    int sum = 0;
    int i = 1;

    while(i <= N){
        sum += getData(List_Row, i, j);
        i += 2;
    }

    return sum;
}

int getData(ELEM* List_Row, int i, int j){ // Поиск значения элемента матрицы по индексу
    ELEM* ListCpy = List_Row;
    while(ListCpy){
        if(ListCpy->row == i){
            while(ListCpy){
                if(ListCpy->col == j){
                    return ListCpy->num;
                } else ListCpy = ListCpy->right;
            }
            return 0;
        }
        ListCpy = ListCpy->down;
    }
    return 0;
}

ELEM* initCol(ELEM *List_Col, int i){  //Создание списка колонок
    ELEM *tmp = new ELEM;
    tmp->row = 0;
    tmp->col = N-i;
    tmp->right = List_Col;
    tmp->down = NULL;
    List_Col = tmp;

    return List_Col;
}

ELEM* initRow(ELEM *List_Row, int i){ //Создание списка строк
    ELEM *tmp = new ELEM;
    tmp->col = 0;
    tmp->row = N-i;
    tmp->down = List_Row;
    tmp->right = NULL;
    List_Row = tmp;

    return List_Row;
}

ELEM* findCol(ELEM *List_Col, int i){ //Поиск колонки по индексу
    while(List_Col){
        if(List_Col->col == i){
            while(List_Col->down){
                List_Col = List_Col->down;
            }
            return List_Col;
        }
        List_Col = List_Col->right;
    }
    return NULL;
}

ELEM* findRow(ELEM *List_Row, int i){ // Поиск строки по индексу
    while(List_Row){
        if(List_Row->row == i){
            while(List_Row->right){
                List_Row = List_Row->right;
            }
            return List_Row;
        }
        List_Row = List_Row->down;
    }
    return NULL;
}

int matrixForm(ELEM *List_Row, ELEM *List_Col){ // Чтение матрицы из файла
    int i = 1; int j = 1, num;

    FILE* file;
    file = fopen("matrix.txt", "r");
    if(!file){
        cout << "Не удалось открыть файл!";
        return 0;
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            fscanf(file, "%d", &num);
            if(num){
                ELEM *tmp = new ELEM;
                tmp->num = num;
                tmp->row = i;
                tmp->col = j;
                tmp->right = NULL;
                tmp->down = NULL;
                findCol(List_Col, j)->down = tmp;
                findRow(List_Row, i)->right = tmp;
            }
        }
    }

    fclose(file);
    return 0;
}

void showMatrix(ELEM *List_Row){ // Вывод матрицы на экран

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cout << getData(List_Row, i, j) << " ";
        } cout << "\n";
    }
}