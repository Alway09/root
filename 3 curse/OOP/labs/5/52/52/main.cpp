#include<iostream>
#include<vector>
#include<string>
#include"classes.h"

void reading(const std::vector<Fax>& v){
    for(size_t i = 0; i < v.size(); ++i){
        std::cout << i+1 << ". " << v[i] << std::endl;
    }
    std::cout << std::endl;
}

void reading_iter(const std::vector<Fax>& v){
    std::vector<Fax>::const_iterator citer(v.cbegin());
    size_t counter(1);
    while(citer != v.cend()){
        std::cout << counter << ". " << *citer << std::endl;
        ++counter;
        ++citer;
    }
    std::cout << std::endl;
}

int main()
{
    //создание и инициализация
    std::vector<Fax> myvect;
    for(unsigned short i = 65; i <= 120; i+=5){
        std::string tempstr;
        for(char j = i; j < i+5; ++j){
            tempstr+=j;
        }
        myvect.push_back(Fax(tempstr));
    }

    //чтение
    reading(myvect);

    //перезапись
    std::vector<Fax>::iterator iter(myvect.begin());
    int counter(1);
    while(iter != myvect.end()){
        if(counter%2){
            myvect.erase(iter);
        }else{
            iter->rename("new name" + std::to_string(counter));
        }

        ++counter;
        ++iter;
    }

    //чтение с использованием итератеров
    reading_iter(myvect);

    //создание копии объекта
    auto myvect_cpy(myvect);

    bool flag(true);
    while(flag)
    try{
        std::cout << "Введите индекс элемента начала удаления: ";
        size_t start(0);
        std::cin >> start;
        if(start == 0 || start >= myvect.size()) throw 1;

        std::cout << "Введите количество удаляемых элементов: ";
        size_t n;
        std::cin >> n;
        if(start+n >= myvect.size()) throw 2;

        iter = myvect.begin();
        myvect.erase(iter+start, iter+start+n);
        myvect.insert(iter+start, myvect_cpy.begin(), myvect_cpy.end());
        flag = false;
    }
    catch(int id){
        switch (id){
        case 1:
            std::cout << "Индекс элемента начала удаления выходит за пределы размера вектора. Попробуйте снова.\n\n";
            break;
        case 2:
            std::cout << "Такое количество элементов не может быть удалено. Попробуйте снова.\n\n";
            break;
        default:
            break;
        }
    }

    reading_iter(myvect);
    reading_iter(myvect_cpy);

}
