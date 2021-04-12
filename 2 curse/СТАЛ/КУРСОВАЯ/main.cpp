#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

const char* filename = "baza.txt";

int noteAmount(){
    int n = 0;
    char buf[35];
    FILE* file;
    file = fopen("baza.txt", "r");
    char* ptr = fgets(buf, 50, file);

    while(!feof(file)){
        ptr = fgets(buf, 50, file);
        n+=1;
    }

    fclose(file);
    return n/5;
};int N = noteAmount();

int* index = (int*)malloc(N*sizeof(int)); // Индексный массив

struct person{
    char fio[32];
    char street[18];
    short int building;
    short int flat;
    char date[10];
};

person** mass = (person**)malloc(N*sizeof(person*));

//-------------------------------------------------
struct list{
    person* data;
    list* ptr;
};
struct queue{
    list *head, *tail;
};

void init(queue* q){  // Инициализация очереди
    q->head = NULL;
    q->tail = NULL;
}

int isempty(queue* q){ // Проверка очереди на пустоту. 1-пустая, 0 - непустая
    if(q->head == NULL) return 1;
    else return 0;
}

void insert(queue* q, person* data){ // Вставка элемента в очередь
    if(q->head == NULL && q->tail == NULL){
        q->head = (list*)malloc(sizeof(list));
        q->tail = (list*)malloc(sizeof(list));
        q->head->data = data;
        q->head->ptr = q->tail;
        q->tail = q->head;
        q->tail->ptr = NULL;
    } else{
        list* tmp = (list*)malloc(sizeof(list));
        tmp->data = data;
        tmp->ptr = NULL;
        q->tail->ptr = tmp;
        q->tail = tmp;
    }
}

void personOutForQueue(person* p){ // Вывод для очереди
    cout << p->fio << " " << p->street << " " << p->building << " " << p->flat << " " << p->date;
}

void printQueue(queue* q){ // Вывод очереди на экран
    list* h = q->head;

    if(isempty(q) == 1){
        cout << "Queue is empty!" << "\n";
        return;
    }
    while(h){
        personOutForQueue(h->data);
        h = h->ptr;
    }
}

void deleteQueue(queue* q){ // Удаление очереди
    if(isempty(q) == 1){
        free(q);
        return;
    }
    bool flag = true;

    while(flag){
        list* tmp;
        tmp = q->head;
        q->head = q->head->ptr;
        free(tmp);
        if(isempty(q) == 1){
            flag = false;
        }
    }
    free(q);
}
//-------------------------------------------------

void read(person* mass[]){ // Чтение из файла с формированием индексного массива
    FILE* file = fopen(filename, "r");
    if(!file){
        cout << "Не удалось открыть файл! Выход из программы!" << "\n";
        exit(1);
    }
    char buf[33];
    int ind = 0;
    char* ptr;

    while(!feof(file)){
        mass[ind] = (person*)malloc(sizeof(person));
        fgets(mass[ind]->fio, 32, file);
        mass[ind]->fio[29] = ' ';
        fgets(mass[ind]->street, 18, file);
        mass[ind]->street[15] = ' ';
        fscanf(file, "%hu", &mass[ind]->building);
        fscanf(file, "%hu", &mass[ind]->flat);
        getc(file);
        fgets(mass[ind]->date, 12, file);
        mass[ind]->date[10] = ' ';
        index[ind] = ind;

        ind++;
    }
    fclose(file);
}

void swap(int* a, int* b){
    int* c = a;
    a = b;
    b = c;
}

int dateCmp(char d1[], char d2[]){ // Сравнение даты. 1-первая больше, 2-вторая больше, 0-равны
    char year1[3], year2[3], month1[3], month2[3], day1[3], day2[3];
    int y1, y2, m1, m2, day11, day22;

    year1[0] = d1[6]; year1[1] = d1[7]; year1[2] = '\0';
    year2[0] = d2[6]; year2[1] = d2[7]; year2[2] = '\0';
    month1[0] = d1[3]; month1[1] = d1[4]; month1[2] = '\0';
    month2[0] = d2[3]; month2[1] = d2[4]; month2[2] = '\0';
    day1[0] = d1[0]; day1[1] = d1[1]; day1[2] = '\0';
    day2[0] = d2[0]; day2[1] = d2[1]; day2[2] = '\0';
    y1 = atoi(year1); y2 = atoi(year2);
    m1 = atoi(month1); m2 = atoi(month2);
    day11 = atoi(day1); day22 = atoi(day2);

    if(y1 > y2) return 1;
        else if(y1 < y2) return 2;
            else if(m1 > m2) return 1;
                else if(m1 < m2) return 2;
                    else if(day11 > day22) return 1;
                        else if(day11 < day22) return 2;
                            else return 0;
}

int streetCmp(char s1[], char s2[]){ // Сравнение названия улиц. 1-первое больше, 2-второе больше, 0-одиинаковые
    
    for(int i = 0; i < 16; i++){
        if(s1[i] > s2[i]) return 1;
        else if(s1[i] < s2[i]) return 2;
    }
    return 0;
}

void downHeap(int root, int n){ // Формирование пирамиды
    int max_child;
    bool flag = true;

    while(root*2 <= n && flag){
        if(root*2 == n){ // Нахождение максимального сына
            max_child = root*2;
        } else if(dateCmp(mass[index[root*2]]->date, mass[index[root*2+1]]->date) == 1){
            max_child = root*2;
        } else if(dateCmp(mass[index[root*2]]->date, mass[index[root*2+1]]->date) == 0){
            if(streetCmp(mass[index[root*2]]->street, mass[index[root*2+1]]->date) == 1){
                max_child = root*2;
            } else max_child = root*2+1;
        } else max_child = root*2+1;

        if(dateCmp(mass[index[root]]->date, mass[index[max_child]]->date) == 2){ // Проверка условия пирамиды (корень больше листьев)
            swap(index[max_child], index[root]);
            root = max_child;
        } else if(dateCmp(mass[index[root]]->date, mass[index[max_child]]->date) == 0){
            if(streetCmp(mass[index[root]]->street, mass[index[max_child]]->street) == 2){
                swap(index[max_child], index[root]);
                root = max_child;
            } else flag = false;
        } else flag = false;
    }
}

void heapSort(){ // Пирамидальная сортировка по возрастанию
    for(int i = (N-1)/2; i >= 0; i--){
        downHeap(i, N-1);
    }
    for(int i = N-1; i >= 1; i--){
        swap(index[0], index[i]);
        downHeap(0, i-1);
    }
}

void personOut(int i){
    cout << mass[i]->fio << " " << mass[i]->street << " " << mass[i]->building << " " << mass[i]->flat << " " << mass[i]->date;
}

int yearCmp(char s1[], int K){ // Сравнение года с ключем. 1-строка больше ключа, 2-ключ бльше строки, 0-
    char year[3];
    int y;
    year[0] = s1[6]; year[1] = s1[7]; year[2] = '\0';
    y = atoi(year);

    if(y > K) return 1;
        else if(y < K) return 2;
            else return 0;
}

void binarySearch(int K){// Бинарный поиск по отсортированному массиву
    queue* q = (queue*)malloc(sizeof(queue));
    init(q);
    int left = 0, right = N-1, m, j;
    while(left<right){
        m = (left+right)/2;
        if(yearCmp(mass[index[m]]->date, K) == 2) left = m+1;
        else right = m;
    }

    if(right != 0){
        if(yearCmp(mass[index[right-1]]->date, K) == 0){
            for(j = right-1; j >= 0; j--){   
                if(yearCmp(mass[index[j]]->date, K) != 0){
                    j++;
                    break;
                }
            }
        } else j = right;
    } else j = right;


    for(int i = j; i < N; i++){
        if(yearCmp(mass[index[i]]->date, K) == 0){
            insert(q, mass[index[i]]);
        } else break;
    }

    printQueue(q);
    deleteQueue(q);
}

void clearScreen(){// Процедура очистки экрана
    cout << "\033[2J\033[1;1H";
}

int main(){
    int ansMain, temp, i, K;
    char ans;
    bool flag = true, flag1 = true;

    read(mass);
    heapSort();

    while(flag)
    {   
        clearScreen();
        cout << "Данные считаны из файла \"" << filename << "\"\n";
        cout << "Количество элементов в базе данных: " << N << "\n";
        cout << "--------------------------------------------------\n";
        cout << "  1. Вывести базу данных на экран.\n";
        cout << "  2. Сортировать базу данных и вывести ее на экран.\n";
        cout << "  3. Найти в базе данных записи по ключу поиска.\n\n";
        cout << "  0. Выйти из программы.\n\n    >";
        cin >> ansMain;

        switch (ansMain)
        {
        case 1:
            clearScreen();
            for(i = 0; i < N; i++){
                if((i+1) < 10) cout << " ";
                cout << " " << i+1 << ". ";
                personOut(i);

                if((i+1) % 20 == 0)
                {   
                    m1: 
                    cout << "Продолжить? (y или n)... ";
                    cin >> ans;
                    
                    if(ans == 'y') clearScreen();
                    else if(ans == 'n') break;
                    else goto m1;
                }
            }

            if(i == N){
                cout << "\n------------------------КОНЕЦ БАЗЫ ДАННЫХ------------------------\n\n";
                cout << "Для продолжения введите любую цифру... ";
                cin >> temp;
            }
            break;

        case 2:
            clearScreen();
            for(i = 0; i < N; i++){
                if((i+1) < 10) cout << " ";
                cout << " " << i+1 << ". ";
                personOut(index[i]);

                if((i+1) % 20 == 0)
                {   
                    m2: 
                    cout << "Продолжить? (y или n)... ";
                    cin >> ans;
                    
                    if(ans == 'y') clearScreen();
                    else if(ans == 'n') break;
                    else goto m2;
                }
            }

            if(i == N){
                cout << "\n------------------------КОНЕЦ БАЗЫ ДАННЫХ------------------------\n\n";
                cout << "Для продолжения введите любую цифру... ";
                cin >> temp;
            }
            break;

        case 3:
            clearScreen();

            cout << "Введите год поселения (две последние цифры года): ";
            cin >> K;
            binarySearch(K);

            cout << "\n--------------------------КОНЕЦ ОЧЕРЕДИ--------------------------\n\n";
            cout << "Для продолжения введите любую цифру... ";
            cin >> temp;
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