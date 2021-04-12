#include<iostream>
#include<vector>
#include<string>

void reading(const std::vector<std::string>& v){
    for(size_t i = 0; i < v.size(); ++i){
        std::cout << i+1 << ". " << v[i].data() << std::endl;
    }
    std::cout << std::endl;
}

void reading_iter(const std::vector<std::string>& v){
    std::vector<std::string>::const_iterator citer(v.cbegin());
    size_t counter(1);
    while(citer != v.cend()){
        std::cout << counter << ". " << citer->data() << std::endl;
        ++counter;
        ++citer;
    }
    std::cout << std::endl;
}

int main()
{
    //создание и инициализация
    std::vector<std::string> myvect;
    for(unsigned short i = 65; i <= 120; i+=5){
        std::string tempstr;
        for(char j = i; j < i+5; ++j){
            tempstr+=j;
        }
        myvect.push_back(tempstr);
    }

    //чтение
    reading(myvect);

    //перезапись
    std::vector<std::string>::iterator iter(myvect.begin());
    int counter(1);
    while(iter != myvect.end()){
        if(counter%2){
            myvect.erase(iter);
        }else{
            for(int i = 0; i < counter; ++i)
                iter->insert(2, "*");
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
        std::cout << "Введите индекс элемента начала удаления: " << std::endl;
        size_t start;
        std::cin >> start;
        if(start == 0 || start >= myvect.size()) throw 1;

        std::cout << "Введите количество удаляемых элементов: ";
        int n;
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
