#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//-----------------------------------------
const unsigned short int stud = 20, academ_num = 5;

struct DATE
{
    string day;
    string month;
    string year;
};

struct LIST
{
    bool academ = false;
    short int num;
    string book_number;
    string fio;
    string age;
    DATE academ_start;
    DATE academ_finish;

    int ptr;
};

int grForm(LIST* group, int len); // Функция формирования групп из файла
void grOut(LIST* group, int gr_head); // Функция вывода списка группы на экран
void addStud(LIST* group, int* gr_free, int* gr_head); // Функция добавления студента в группу
bool removeStud(LIST* group, int* gr_free, int* gr_head, string fio); // Функция удаления студента из группы
int studAmount(LIST* group, int gr_head); // Функция подсчета количества студентов в группе
bool searchStud(LIST* group, int gr_head, int param); // Функция поиска студента по параметру
void showStud(LIST* group, int head); // Функция вывода информации о студенте
bool changeStud(LIST* group,int gr_head, string fio); // Функция изменения информации о студенте
int vacation(LIST* group, int gr_head, string fio); // Функция подсчета длительности академического отпуска студента
bool transfer(LIST* from, LIST* to, int* from_head, int* from_free, int* to_head, int* to_free, string fio); //Функция перевода студента из одной группы в другую
bool inAcadem(LIST* from, LIST* to, int* from_head, int* from_free, int* to_head, int* to_free, string fio); //Функция отправки студента из группы в академический отпуск
bool fromAcadem(LIST* academ, LIST* gr1, LIST* gr2, int* academ_head, int* academ_free, int* gr1_head, int* gr1_free, int* gr2_head, int* gr2_free, string fio); // Функция возврата студента из академического отпуска

unsigned short int mainMenu();
void clearDisplay();

int main()
{
    unsigned short int ans;
    clearDisplay();

    /*
    LIST PO[stud];
    int po_head = 0;
    PO[po_head].ptr = -1;
    int po_free = 1;
    for(int i = 1; i < stud-1; i++)
    {
        PO[i].ptr = i+1;
    }
    PO[stud-1].ptr = -1;

    LIST MMI[stud];
    int mmi_head = 0;
    MMI[mmi_head].ptr = -1;
    int mmi_free = 1;
    for(int i = 1; i < stud-1; i++)
    {
        MMI[i].ptr = i+1;
    }
    MMI[stud-1].ptr = -1;*/

    LIST ACADEM[stud];
    int academ_head = 0;
    ACADEM[academ_head].ptr = -1;
    int academ_free = 1;
    for(int i = 1; i < stud-1; i++)
    {
        ACADEM[i].ptr = i+1;
    }
    ACADEM[stud-1].ptr = -1;
    

    ///*    
    LIST PO[stud]; PO[0].num = 1;
    int po_head = 0;
    int po_free = grForm(PO, stud);
    LIST MMI[stud]; MMI[0].num = 2;
    int mmi_head = 0;
    int mmi_free = grForm(MMI, stud);
    //LIST ACADEM[stud]; ACADEM[0].num = academ_num;
    //int academ_head = 0;
    //int academ_free = grForm(ACADEM, stud);
    //*/

    string fio;
    bool flag;
    unsigned short int ans1;

    main_menu:
    clearDisplay();
    ans = mainMenu();
    clearDisplay();

    switch (ans)
    {
    case 0:
        goto exit;
        break;

    case 1:
        again_1:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n\n   >";
        cin >> ans; cout << "\n";

        switch (ans)
        {
        case 1:
            addStud(PO, &po_free, &po_head);
            break;
        
        case 2:
            addStud(MMI, &mmi_free, &mmi_head);
            break;

        case 3:
            ACADEM[0].num = academ_num;
            addStud(ACADEM, &academ_free, &academ_head);
            break;

        default:
            local_1:
            cout << "\nНет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_1;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_1;
                break;
            }
            break;
        }

        cout << "\nОперация выполнена!\n";
        cout << "  1. Вернутся в главное меню\n";
        cout << "  2. Выйти из программы\n\n   >";
        cin >> ans;
        switch (ans)
        {
        case 1:
            goto main_menu;
            break;

        case 2:
            goto exit;
            break;
            
        default:
            goto main_menu;
            break;
        }
        break;

    case 2:
        again_2:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            if(PO[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 2:
            if(MMI[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 3:
            if(ACADEM[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;
        
        default:
            goto local_2;
            break;
        }

        cout << "\n Введите ФИО студента: ";
        cin.ignore();
        getline(cin, fio);

        switch (ans)
        {
        case 1:
            flag = removeStud(PO, &po_free, &po_head, fio);
            break;

        case 2:
            flag = removeStud(MMI, &mmi_free, &mmi_head, fio);
            break;

        case 3:
            flag = removeStud(ACADEM, &academ_free, &academ_head, fio);
            break;
        
        default:
            local_2:
            cout << "\nНет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_2;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_2;
                break;
            }
            break;
        }

        if(flag){
            cout << "\nСтудент не найден!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_2;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_2;
                break;
            }
        } else {
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }

    case 3:
        int amount;
        again_3:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            amount = studAmount(PO, po_head);
            cout << "\nКоличество студентов в группе ПО: " << amount;
            break;

        case 2:
            amount = studAmount(MMI, mmi_head);
            cout << "\nКоличество студентов в группе ММИ: " << amount;
            break;

        case 3:
            amount = studAmount(ACADEM, academ_head);
            cout << "\nКоличество студентов в группе АКАДЕМ: " << amount;
            break;
        
        default:
            cout << "\nНет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_3;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                break;
            }
            break;
        }

        cout << "\n  1. Вернутся в главное меню\n";
        cout << "  2. Выйти из программы\n\n   >";
        cin >> ans; cout << "\n";
        switch (ans)
        {
        case 1:
            goto main_menu;
            break;

        case 2:
            goto exit;
            break;
            
        default:
            goto main_menu;
            break;
        }

    case 4:
        again_4:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            if(PO[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 2:
            if(MMI[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 3:
            if(ACADEM[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;
        
        default:
            goto local_4;
            break;
        }

        cout << "Выберите параметр поиска:\n";
        cout << "  1. Поиск по ФИО\n";
        cout << "  2. Поиск по номеру зачетной книжки\n";
        cout << "  3. Поиск по возрасту\n";
        cout << "  4. Поиск по дате начала академического отпуска\n";
        cout << "  5. Поиск по дате конца академического отпуска\n\n   >";
        cin >> ans1;

        switch (ans)
        {
        case 1:
            switch (ans1)
            {
            case 1:
            case 2:
            case 3:
                flag = searchStud(PO, po_head, ans1);
                break;

            default:
                cout << "Нет такого параметра для указанной группы!\n";
                local_4:
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Ввести ответ заново\n";
                cout << "  3. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    clearDisplay();
                    goto again_4;
                    break;

                case 3:
                    goto exit;
                    break;
            
                default:
                    goto local_4;
                    break;
                } 
                break;
            }
            break;
        
        case 2:
            switch (ans1)
            {
            case 1:
            case 2:
            case 3:
                flag = searchStud(MMI, mmi_head, ans1);
                break;

            default:
                cout << "Нет такого параметра для указанной группы!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Ввести ответ заново\n";
                cout << "  3. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    clearDisplay();
                    goto again_4;
                    break;

                case 3:
                    goto exit;
                    break;
            
                default:
                    goto local_4;
                    break;
                } 
                break;
            }
            break;

        case 3:
            switch (ans1)
            {
            case 1:
            case 4:
            case 5:
                flag = searchStud(ACADEM, academ_head, ans1);
                break;
            
            default:
                cout << "Нет такого параметра для указанной группы!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Ввести ответ заново\n";
                cout << "  3. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    clearDisplay();
                    goto again_4;
                    break;

                case 3:
                    goto exit;
                    break;

                default:
                    goto local_4;
                    break;
                }
            }
            break;

        default:
            cout << "\nНет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_4;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_4;
                break;
            }
            break;
        }

        if(flag){
            cout << "\nСтудент не найден!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_4;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_4;
                break;
            } 
        } else {
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                break;
            }
        }

    case 5:
        again_5:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            if(PO[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 2:
            if(MMI[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 3:
            if(ACADEM[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;
        
        default:
            break;
        }

        cout << "\n Введите ФИО студента: ";
        cin.ignore();
        getline(cin, fio);

        switch (ans)
        {
        case 1:
            flag = changeStud(PO, po_head, fio);
            break;

        case 2:
            flag = changeStud(MMI, mmi_head, fio);
            break;
        
        case 3:
            flag = changeStud(ACADEM, mmi_head, fio);
            break;

        default:
            local_5:
            cout << "Нет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_5;
                break;

            case 3:
                goto exit;
                break;

            default:
                goto local_5;
                break;
            }
            break;
        }

        if(flag){
            cout << "\nСтудент не найден!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_5;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_5;
                break;
            } 
        } else {
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }

    case 6:
        again_6:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n";
        cout << "  3. АКАДЕМ\n\n   >";
        cin >> ans; cout << "\n";

        switch (ans)
        {
        case 1:
            grOut(PO, po_head);
            break;

        case 2:
            grOut(MMI, mmi_head);
            break;

        case 3:
            grOut(ACADEM, academ_head);
            break;
        
        default:
            local_6:
            cout << "Нет такого варианта ответа!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_6;
                break;

            case 3:
                goto exit;
                break;

            default:
                goto local_6;
                break;
            }
            break;
        }

        cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }

    case 7:
        again_7:
        cout << "Перевести студента из группы: \n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n\n   >";
        cin >> ans; cout << "\n";

        switch (ans)
        {
        case 1:
            if(PO[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 2:
            if(MMI[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        default:
            break;
        }

        cout << "В группу: \n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n\n   >";
        cin >> ans1; cout << "\n";

        switch (ans)
        {
        case 1:
            switch (ans1)
            {
            case 2:
                cout << "Введите  ФИО: ";
                cin.ignore();
                getline(cin, fio);
                flag = transfer(PO, MMI, &po_head, &po_free, &mmi_head, &mmi_free, fio);
                break;
            
            case 3:
                cout << "Введите  ФИО: ";
                cin.ignore();
                getline(cin, fio);
                flag = transfer(PO, ACADEM, &po_head, &po_free, &academ_head, &academ_free, fio);
                break;

            default:
                cout << "Невозможно выполнить операцию!\n";
                local_7:
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Ввести ответ заново\n";
                cout << "  3. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    clearDisplay();
                    goto again_7;
                    break;

                case 3:
                    goto exit;
                    break;

                default:
                    goto local_7;
                    break;
                }
                break;
            }
            break;

        case 2:
            switch (ans1)
            {
            case 1:
                cout << "Введите  ФИО: ";
                cin.ignore();
                getline(cin, fio);
                flag = transfer(MMI, PO, &mmi_head, &mmi_free, &po_head, &po_free, fio);
                break;
            
            case 3:
                cout << "Введите  ФИО: ";
                cin.ignore();
                getline(cin, fio);
                flag = transfer(MMI, ACADEM, &mmi_head, &mmi_free, &academ_head, &academ_free, fio);
                break;

            default:
                cout << "Невозможно выполнить операцию!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Ввести ответ заново\n";
                cout << "  3. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    clearDisplay();
                    goto again_7;
                    break;

                case 3:
                    goto exit;
                    break;

                default:
                    goto local_7;
                    break;
                }
                break;
            }
            break;

        default:
            cout << "Невозможно выполнить операцию!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_7;
                break;

            case 3:
                goto exit;
                break;

            default:
                goto local_7;
                break;
            }
            break;
        }

        if(flag){
            cout << "\nСтудент не найден!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_7;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_7;
                break;
            } 
        } else {
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }
        break;

    case 8:
        if(ACADEM[academ_head].ptr == -1){
            cout << "Список АКАДЕМ пуст!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }

        again_8:
        cout << "Введите ФИО студента: ";
        cin.ignore();
        getline(cin, fio);

        if(vacation(ACADEM, academ_head, fio) == 0){
            cout << "\nСтудент не найден!";
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
                case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_8;
                break;

            case 3:
                goto exit;
                break;

            default:
                goto main_menu;
                break;
            }
        }

        cout << "Длительность отпуска в месяцах: " << vacation(ACADEM, academ_head, fio) << "\n";

        cout << "\n  1. Вернутся в главное меню\n";
        cout << "  2. Ввести ответ заново\n";
        cout << "  3. Выйти из программы\n\n   >";
        cin >> ans;
        switch (ans)
        {
        case 1:
            goto main_menu;
            break;

        case 2:
            clearDisplay();
            goto again_8;
            break;

        case 3:
            goto exit;
            break;

        default:
            goto main_menu;
            break;
        }
        break;

    case 9:
        again_9:
        cout << "Выберите группу:\n";
        cout << "  1. ПО\n";
        cout << "  2. ММИ\n\n   >";
        cin >> ans;

        switch (ans)
        {
        case 1:
            if(PO[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;

        case 2:
            if(MMI[po_head].ptr == -1){
                cout << "\nСписок пуст!\n";
                cout << "  1. Вернутся в главное меню\n";
                cout << "  2. Выйти из программы\n\n   >";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    goto main_menu;
                    break;

                case 2:
                    goto exit;
                    break;
            
                default:
                    goto main_menu;
                    break;
                }
            }
            break;
        
        default:
            goto local_9;
            break;
        }

        cout << "\n Введите ФИО студента: ";
        cin.ignore();
        getline(cin, fio);

        switch(ans){
        case 1:
            flag = inAcadem(PO, ACADEM,&po_head, &po_free, &academ_head, &academ_free, fio);
            break;

        case 2:
            flag = inAcadem(MMI, ACADEM,&mmi_head, &mmi_free, &academ_head, &academ_free, fio);
            break;
        }

        if(!flag){
            cout << "\nСтудент не найден!\n";
            local_9:
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_9;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_9;
                break;
            } 
        } else {
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }
        break;

    case 10:
        again_10:
        if(ACADEM[academ_head].ptr == -1){
            cout << "\nСписок АКАДЕМ пуст!\n";
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
        
            default:
                goto main_menu;
                break;
            }
        }

        cout << "\n Введите ФИО студента: ";
        cin.ignore();
        getline(cin, fio);

        flag = fromAcadem(ACADEM, PO, MMI, &academ_head, &academ_free, &po_head, &po_free, &mmi_head, &mmi_free, fio);

        if(flag){
            cout << "\nСтудент не найден!\n";
            local_10:
            cout << "  1. Вернутся в главное меню\n";
            cout << "  2. Ввести ответ заново\n";
            cout << "  3. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                clearDisplay();
                goto again_10;
                break;

            case 3:
                goto exit;
                break;
            
            default:
                goto local_10;
                break;
            } 
        } else {
            cout << "\n  1. Вернутся в главное меню\n";
            cout << "  2. Выйти из программы\n\n   >";
            cin >> ans;
            switch (ans)
            {
            case 1:
                goto main_menu;
                break;

            case 2:
                goto exit;
                break;
            
            default:
                goto main_menu;
                break;
            }
        }
        break;

    default:
        goto main_menu;
        break;
    }
    
exit:
    clearDisplay();
    return 0;
}

unsigned short int mainMenu(){
    int ans;

    cout << "--------------------------------------INFO--------------------------------------";
    cout << "   Формат записи даты: дд.мм.гггг\n";
    cout << "   Существующие списки групп: ПО, ММИ, АКАДЕМ(изначально пуст)\n";
    cout << "   Максимальное число cтудентов в  группе: " << stud << "\n";
    cout << "--------------------------------------------------------------------------------";
    cout << "Выберите операцию: \n";
    cout << "  1. Добавить студента в группу\n";
    cout << "  2. Удалить студента из группы\n";
    cout << "  3. Вывести на экран количество студентов в группе\n";
    cout << "  4. Поиск студента в группе по параметру\n";
    cout << "  5. Редактировать данные о студенте\n";
    cout << "  6. Вывести список группы на экран\n";
    cout << "  7. Перевести студента из одной группы в другую\n";
    cout << "  8. Вывести для указанного студента длительность отпуска в месяцах\n";
    cout << "  9. Отправить студента в академический отпуск\n";
    cout << " 10. Вернуть студента из академического отпуска\n\n";
    cout << "  0. Выйти из программы\n\n   >";

    cin >> ans;

    return ans;
}

void clearDisplay(){
    cout << "\033[2J\033[1;1H";
}

bool inAcadem(LIST* from, LIST* to, int* from_head, int* from_free, int* to_head, int* to_free, string fio){
    int head = *from_head, buf, buf1 = to[*to_free].ptr, k = 0;
    bool flag = true;
    string date_start, date_finish, b_n, age;

    for(int i = 0; i < stud; i++){
        if(head != -1)
        {
            if(from[head].fio == fio)
            {
                to[*to_free].fio = from[head].fio;
                cout << "Введите дату начала академического отпуска: ";
                cin >> date_start;
                cout << "Введите дату конца академическгог отпуска: ";
                cin >> date_finish;

                for(int i = 0; i < 2; i++){
                    to[*to_free].academ_start.day += date_start[k];
                    k++;
                }
                k++;
                for(int i = 0; i < 2; i++){
                    to[*to_free].academ_start.month += date_start[k];
                    k++;
                }
                k++;
                for(int i = 0; i < 4; i++){
                    to[*to_free].academ_start.year += date_start[k];
                    k++;
                }
                k = 0;

                for(int i = 0; i < 2; i++){
                    to[*to_free].academ_finish.day += date_finish[k];
                    k++;
                }
                k++;
                for(int i = 0; i < 2; i++){
                    to[*to_free].academ_finish.month += date_finish[k];
                    k++;
                }
                k++;
                for(int i = 0; i < 4; i++){
                    to[*to_free].academ_finish.year += date_finish[k];
                    k++;
                }

                from[head].academ = true;

                to[*to_free].ptr = *to_head;
                *to_head = *to_free;
                *to_free = buf1;

                break;
            }
            buf = head;
            head = from[head].ptr;
        } else {
            flag = false;
            return flag;
        }
    }

    return flag;
}

bool fromAcadem(LIST* academ, LIST* gr1, LIST* gr2, int* academ_head, int* academ_free, int* gr1_head, int* gr1_free, int* gr2_head, int* gr2_free, string fio){
    bool flag;
    int head1 = *gr1_head, head2 = *gr2_head, buf;

    flag = removeStud(academ, academ_free, academ_head, fio);

    if(!flag){
        for(int i = 0; i < stud; i++){
            if(gr1[head1].fio == fio){
                gr1[head1].academ = false;
                return flag;
            } else{
                buf = head1;
                head1 = gr1[head1].ptr;
            }
        }

        for(int i = 0; i < stud; i++){
            if(gr2[head2].fio == fio){
                gr2[head2].academ = false;
                return flag;
            } else{
                buf = head2;
                head2 = gr2[head2].ptr;
            }
        }
    }

    return flag;
}

bool transfer(LIST* from, LIST* to, int* from_head, int* from_free, int* to_head, int* to_free, string fio){
    int head = *from_head, buf, buf1 = to[*to_free].ptr, k = 0;
    bool flag = true;
    unsigned short int ans;
    string date_start, date_finish, b_n, age;

    for(int i = 0; i < stud; i++){
        if(head != -1)
        {
            if(from[head].fio == fio)
            {
                if(from[head].academ_start.day == "\0")
                {
                    if(to[*to_head].academ_start.day == "\0")
                    {
                        to[*to_free].book_number = from[head].book_number;
                        to[*to_free].age = from[head].age;
                        to[*to_free].fio = from[head].fio;
                        from[head].fio.clear();
                        from[head].book_number.clear();
                        from[head].age.clear();
                        flag = false;

                        if(i == 0){
                            *from_head = from[head].ptr;
                            from[head].ptr = *from_free;
                            *from_free = head;
                            break;
                        } 
                        from[buf].ptr = from[head].ptr;
                        from[head].ptr = *from_free;
                        *from_free = head;

                        to[*to_free].ptr = *to_head;
                        *to_head = *to_free;
                        *to_free = buf1;

                        break;
                    } else {
                        cout << "При переводе студента " << fio << " сотрутся его номер зачетной книжки и возраст. Продолжить? (1-да, 2-нет): ";
                        cin >> ans;
                        if(ans == 1){
                            to[*to_free].fio = from[head].fio;
                            from[head].fio.clear();
                            from[head].book_number.clear();
                            from[head].age.clear();
                            cout << "Введите дату начала академического отпуска: ";
                            cin >> date_start;
                            cout << "Введите дату конца академическгог отпуска: ";
                            cin >> date_finish;

                            for(int i = 0; i < 2; i++){
                                to[*to_free].academ_start.day += date_start[k];
                                k++;
                            }
                            k++;
                            for(int i = 0; i < 2; i++){
                                to[*to_free].academ_start.month += date_start[k];
                                k++;
                            }
                            k++;
                            for(int i = 0; i < 4; i++){
                                to[*to_free].academ_start.year += date_start[k];
                                k++;
                            }
                            k = 0;

                            for(int i = 0; i < 2; i++){
                                to[*to_free].academ_finish.day += date_finish[k];
                                k++;
                            }
                            k++;
                            for(int i = 0; i < 2; i++){
                                to[*to_free].academ_finish.month += date_finish[k];
                                k++;
                            }
                            k++;
                            for(int i = 0; i < 4; i++){
                                to[*to_free].academ_finish.year += date_finish[k];
                                k++;
                            }

                            if(i == 0){
                            *from_head = from[head].ptr;
                            from[head].ptr = *from_free;
                            *from_free = head;
                            break;
                            } 
                            from[buf].ptr = from[head].ptr;
                            from[head].ptr = *from_free;
                            *from_free = head;

                            to[*to_free].ptr = *to_head;
                            *to_head = *to_free;
                            *to_free = buf1;

                            break;
                        } else{
                            flag = false;
                            break;
                        }
                    }
                } else {
                    cout << "При переводе студента " << fio << " сотрутся даты начала и конца его академического отпуска. Продолжить? (1-да, 2-нет): ";
                    cin >> ans;
                    if(ans == 1){
                        to[*to_free].fio = from[head].fio;
                        from[head].fio.clear();
                        from[head].academ_start.day.clear();
                        from[head].academ_start.month.clear();
                        from[head].academ_start.year.clear();
                        from[head].academ_finish.day.clear();
                        from[head].academ_finish.month.clear();
                        from[head].academ_finish.year.clear();
                        flag = false;
                        cout << "Введите номер зачетной книжки: ";
                        cin >> b_n;
                        cout << "Введите возраст: ";
                        cin >> age;

                        to[*to_free].book_number = b_n;
                        to[*to_free].age = age;

                        if(i == 0){
                            *from_head = from[head].ptr;
                            from[head].ptr = *from_free;
                            *from_free = head;
                            break;
                        } 
                        from[buf].ptr = from[head].ptr;
                        from[head].ptr = *from_free;
                        *from_free = head;

                        to[*to_free].ptr = *to_head;
                        *to_head = *to_free;
                        *to_free = buf1;

                        break;
                    }
                }
                flag = false;
            }
            buf = head;
            head = from[head].ptr;
        } else{
            break;
        }
    }
    return flag;
}

int vacation(LIST* group, int gr_head, string fio){
    bool flag = true;
    int head = gr_head, result = 0, tmp;

    for(int i = 0; i < stud; i++)
    {
        if(head != -1){
            if(group[head].fio == fio){
                result = stoi(group[head].academ_finish.month) - stoi(group[head].academ_start.month); 
                tmp = stoi(group[head].academ_finish.year) - stoi(group[head].academ_start.year);
                if((result < 0 && tmp == 1) || (result > 0 && tmp == 1)){
                    result += 12;
                } else if((result == 0 && tmp == 2)){
                    result += 24;
                }
                return result;
                flag = false;
                break;
            }
            head = group[head].ptr;
        } else{
            break;
        }
    }
    return 0;
}

bool changeStud(LIST* group,int gr_head, string fio){
    int head = gr_head;
    int ans, k = 0;
    string tmp, day, month, year;
    bool flag = true;

    for(int i = 0; i < stud; i++){
        if(group[head].fio == fio)
        {
            cout << "\n";
            showStud(group, head);
            cout << "\n";

            cout << "Изменить ФИО студента? (1-да; 2-нет): ";
            cin >> ans;
            if(ans == 1){
                cout << "Введите ФИО: ";
                cin.ignore();
                getline(cin,tmp);
                group[head].fio = tmp;
                cout << "\n";
                showStud(group, head);
                cout << "\n";
                tmp.clear();
            }

            if(group[head].academ_start.day == "\0")
            {

                cout << "Изменить номер зачетной книжки студента? (1-да; 2-нет): ";
                cin >> ans;
                if(ans == 1){
                    cout << "Введите номер зачетной книжки: ";
                    cin >> tmp;
                    group[head].book_number = tmp;
                    cout << "\n";
                    showStud(group, head);
                    cout << "\n";
                    tmp.clear();
                }

                cout << "Изменить возраст студента? (1-да; 2-нет): ";
                cin >> ans;
                if(ans == 1){
                    cout << "Введите возраст: ";
                    cin >> tmp;
                    group[head].age = tmp;
                    cout << "\n";
                    showStud(group, head);
                    cout << "\n";
                    tmp.clear();
                }
            } else {
                cout << "Изменить дату начала академического отпуска студента? (1-да; 2-нет): ";
                cin >> ans;
                if(ans == 1){
                    cout << "Введите дату начала академического отпуска: ";
                    cin >> tmp;
                    for(int i = 0; i < 2; i++){
                        day += tmp[k];
                        k++;
                    }
                    k++;
                    for(int i = 0; i < 2; i++){
                        month += tmp[k];
                        k++;
                    }
                    k++;
                    for(int i = 0; i < 4; i++){
                        year += tmp[k];
                        k++;
                    }
                    k = 0;

                    group[head].academ_start.day = day;
                    group[head].academ_start.month = month;
                    group[head].academ_start.year = year;
                    day.clear(); month.clear(); year.clear();tmp.clear();
                    cout << "\n";
                    showStud(group, head);
                    cout << "\n";
                }

                cout << "Изменить дату конца академического отпуска студента? (1-да; 2-нет): ";
                cin >> ans;
                if(ans == 1){
                    cout << "Введите дату конца академического отпуска: ";
                    cin >> tmp;

                    for(int i = 0; i < 2; i++){
                        day += tmp[k];
                        k++;
                    }
                    k++;
                    for(int i = 0; i < 2; i++){
                        month += tmp[k];
                        k++;
                    }
                    k++;
                    for(int i = 0; i < 4; i++){
                        year += tmp[k];
                        k++;
                    }

                    group[head].academ_finish.day = day;
                    group[head].academ_finish.month = month;
                    group[head].academ_finish.year = year;
                    cout << "\n";
                    showStud(group, head);
                    cout << "\n";
                }
            }
            flag = false;
            break;

        } else {
            head = group[head].ptr;
            if(head == -1){
                break;
            }
        }
    }

    return flag;
}

void showStud(LIST* group, int head){
    cout << "  " << group[head].book_number << " " << group[head].fio << " " << 
    group[head].age << " " << " ";
    if(group[head].academ_start.day != "\0"){
        cout << group[head].academ_start.day << "." << group[head].academ_start.month << "." <<
        group[head].academ_start.year << "-" << group[head].academ_finish.day << "." <<
        group[head].academ_finish.month << "." << group[head].academ_finish.year;
    }
    if(group[head].academ){
        cout << "(Студент в отпуске)";
    }
    cout << "\n";
}

bool searchStud(LIST* group, int gr_head, int param){
    int head = gr_head, k = 0;
    bool flag = true;
    string tmp, tmp1, day, month, year;
    
    
    switch (param)
    {
        case 1:
        cout << "Введите ФИО студента: ";
        cin.ignore();
        getline(cin,tmp);
        for(int i = 0; i < stud; i++){
            if(head != -1){
                if(group[head].fio == tmp){
                    showStud(group, head);
                    flag = false;
                }
                head = group[head].ptr;
            } else{
                break;
            }
        }
        break;
    
        case 2:
        cout << "Введите номер зачетной книжки студента: ";
        cin >> tmp;
        for(int i = 0; i < stud; i++){
            if(head != -1){
                if(group[head].book_number == tmp){
                    showStud(group, head);
                    flag = false;
                }
                head = group[head].ptr;
            } else{
                break;
            }
        }
        break;

        case 3:
        cout << "Введите возраст студента: ";
        cin >> tmp;
        for(int i = 0; i < stud; i++){
            if(head != -1){
                if(group[head].age == tmp){
                    showStud(group, head);
                    flag = false;
                }
                head = group[head].ptr;
            } else{
                break;
            }
        }
        break;

        case 4:
        cout << "Введите дату начала академического отпуска студента: ";
        cin >> tmp;

        for(int i = 0; i < 2; i++){
                day += tmp[k];
                k++;
            }
            k++;
            for(int i = 0; i < 2; i++){
                month += tmp[k];
                k++;
            }
            k++;
            for(int i = 0; i < 4; i++){
                year += tmp[k];
                k++;
        }

        for(int i = 0; i < stud; i++){
            if(head != -1){
                if(group[head].academ_start.day == day && group[head].academ_start.month == month && group[head].academ_start.year == year){
                    showStud(group, head);
                    flag = false;
                }
                head = group[head].ptr;
            } else{
                break;
            }
        }
        break;

        case 5:
        cout << "Введите дату конца академического отпуска студента: ";
        cin >> tmp;

        for(int i = 0; i < 2; i++){
                day += tmp[k];
                k++;
            }
            k++;
            for(int i = 0; i < 2; i++){
                month += tmp[k];
                k++;
            }
            k++;
            for(int i = 0; i < 4; i++){
                year += tmp[k];
                k++;
        }

        for(int i = 0; i < stud; i++){
            if(head != -1){

                if(group[head].academ_finish.day == day && group[head].academ_finish.month == month && group[head].academ_finish.year == year){
                    showStud(group, head);
                    flag = false;
                }
                head = group[head].ptr;
            } else{
                break;
            }
        }
        break;

    default:
        break;
    }

    return flag;
}

int studAmount(LIST* group, int gr_head){
    int head = gr_head, counter = 0;

    if(group[head].ptr != -1){
        for(int i = 0; i < stud; i++){
            if(head == -1){
                break;
            }
            counter += 1;
            head = group[head].ptr;
        }
    } else return 0;

    return counter;
}

bool removeStud(LIST* group, int* gr_free, int* gr_head, string fio){
    int head = *gr_head, buf;
    bool flag = true;

    for(int i = 0; i < stud; i++){
        if(group[head].fio == fio){
            flag = false;
            if(group[head].academ){
                cout << "Студент находится в академическом отпуске. Верните его из отпуска и повторите операцию.";
                return flag;
            }
            group[head].book_number.clear();
            group[head].fio.clear();
            group[head].age.clear();
            group[head].academ_finish.day.clear();
            group[head].academ_finish.month.clear();
            group[head].academ_finish.year.clear();
            group[head].academ_start.day.clear();
            group[head].academ_start.month.clear();
            group[head].academ_start.year.clear();
            if(i == 0){
                *gr_head = group[head].ptr;
                group[head].ptr = *gr_free;
                *gr_free = head;
                break;
            } 
            group[buf].ptr = group[head].ptr;
            group[head].ptr = *gr_free;
            *gr_free = head;
            break;
        } else{
            buf = head;
            head = group[head].ptr;
        }
    }
    
    return flag;
}

void grOut(LIST* group, int gr_head){
    int head = gr_head;
    if(group[head].ptr != -1)
    {
        for(int i = 0; i < stud; i++){
            if(head == -1){
                break;
            }
            showStud(group, head);

            head = group[head].ptr;
        }
    } else cout << "Список пуст!\n";
}

void addStud(LIST* group, int* gr_free, int* gr_head){
    string b_n, fio, age, date_s, date_f;
    unsigned short int flag = 0;
    int buf = group[*gr_free].ptr;

    if(*gr_head != -1)
    {
        cout << "Введите данные о студенте \n ФИО: ";
        cin.ignore();
        getline(cin, fio);
        group[*gr_free].fio = fio;
        if(group[0].num != academ_num)
        {
            cout << " Номер зачетной книжки: ";
            getline(cin, b_n);
            cout << " Возраст: ";
            getline(cin, age);

            group[*gr_free].book_number = b_n;
            group[*gr_free].age = age;
            group[*gr_free].ptr = *gr_head;
            *gr_head = *gr_free;
            *gr_free = buf;
        } else {
            cout << " Дату начала академического отпуска: ";
            getline(cin, date_s);

            for(int i = 0; i < 2; i++){
                group[*gr_free].academ_start.day += date_s[flag];
                flag++;
            }
            flag++;
            for(int i = 0; i < 2; i++){
                group[*gr_free].academ_start.month += date_s[flag];
                flag++;
            }
            flag++;
            for(int i = 0; i < 4; i++){
                group[*gr_free].academ_start.year += date_s[flag];
                flag++;
            }
            flag = 0;

            cout << " Дату окончания академического отпуска: ";
            getline(cin, date_f);

            for(int i = 0; i < 2; i++){
                group[*gr_free].academ_finish.day += date_f[flag];
                flag++;
            }
            flag++;
            for(int i = 0; i < 2; i++){
                group[*gr_free].academ_finish.month += date_f[flag];
                flag++;
            }
            flag++;
            for(int i = 0; i < 4; i++){
                group[*gr_free].academ_finish.year += date_f[flag];
                flag++;
            }

            group[*gr_free].ptr = *gr_head;
            *gr_head = *gr_free;
            *gr_free = buf;

        }
    } else cout << "Нет места для записи!\n";
}

int grForm(LIST* group, int len){
    ifstream stream("groups.txt");
    string buf = "0";
    unsigned int flag, amount = 0;

    
    while(getline(stream, buf))
    {
        if((buf[0] - '0') == group[0].num)
        {
            for(int i = 0; i < buf.length(); i++)
            {
                if(buf[i] == ';')
                {
                    amount++;
                }
            };

            amount++;

            if(amount > stud){
                cout << "Недостаточно места в массиве для группы №" << group[0].num << "! Выход из программы!\n";
                exit(0);
            }

            for(int i = 2; i < buf.length(); i++)
            {
                if(buf[i] == '(')
                {
                        flag = i;
                    break;
                }
            };

            for(int j = 0; j < amount; j++)
            {
                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].book_number += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].fio += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].age += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].academ_start.day += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].academ_start.month += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].academ_start.year += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].academ_finish.day += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ',')
                    {
                        flag = i;
                        break;
                    }
                    group[j].academ_finish.month += buf[i];
                };

                for(int i = flag+1; i < buf.length(); i++)
                {
                    if(buf[i] == ';')
                    {
                        group[j].ptr = j + 1;
                        flag = i;
                        break;
                    } else if(buf[i] == ')'){
                        group[j].ptr = -1;
                        flag = i;
                        break;
                    }
                    group[j].academ_finish.year += buf[i];
                };
            }
            for(int i = amount; i < stud-1; i++)
            {
                group[i].ptr = i+1;
            }
            group[stud-1].ptr = -1;
        }
    }

    stream.close();
    return amount+1;
}