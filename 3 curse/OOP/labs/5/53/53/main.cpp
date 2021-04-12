#include<iostream>
#include<vector>
#include<stack>
#include<list>
#include<string>
#include<algorithm>
#include<ctime>
#include<functional>
#include<stdlib.h>
#include"classes.h"

template <class T>
void reading_iter(const T& v){
    typename T::const_iterator citer(v.cbegin());
    size_t counter(1);
    while(citer != v.cend()){
        std::cout << counter << ". " << *citer << std::endl;
        ++counter;
        ++citer;
    }
    std::cout << std::endl;
}

bool comp(const Fax& first, const Fax& second){
    return !(first < second);
}

void reading_stack(const std::stack<Fax>& st){
    if(st.empty()){
        std::cout << "Stack is empty!/n";
        return;
    }

    auto copy(st);
    size_t counter(1);
    while(!copy.empty()){
        std::cout << counter << ". " << copy.top() << std::endl;
        copy.pop();
        ++counter;
    }
    std::cout << std::endl;
}

void copy_if(std::vector<Fax>& vect, std::stack<Fax>& st, const Fax& elem, std::function<bool(const Fax&,const Fax&)> pred){
    std::vector<Fax>::const_iterator iter(vect.cbegin());
    while(iter != vect.cend()){
        if(pred(*iter, elem)){
            st.push(*iter);
        }
        ++iter;
    }
}

void sort_stack(std::stack<Fax>& st, std::function<bool(const Fax&,const Fax&)> comparator){
    if(st.empty()){
        return;
    }

    std::vector<Fax> vect;

    while(!st.empty()){
        vect.push_back(st.top());
        st.pop();
    }

    std::sort(vect.begin(), vect.end(), comparator);

    std::vector<Fax>::iterator iter(vect.end()-1);
    while(iter != vect.begin()-1){
        st.push(*iter);
        --iter;
    }
}
void merge(const std::vector<Fax>& vect, const std::stack<Fax>& st, std::list<Fax>& lst){
    auto st_cpy(st);
    std::vector<Fax> temp_v;

    while(!st_cpy.empty()){
        temp_v.push_back(st_cpy.top());
        st_cpy.pop();
    }

    std::merge(vect.begin(), vect.end(), temp_v.begin(), temp_v.end(), std::back_inserter(lst));
}

int main()
{
    time_t timer;
    std::srand(std::time(&timer));

    //создание и инициализация
    std::vector<Fax> myvect;
    for(unsigned short i = 65; i <= 120; i+=5){
        std::string tempstr;
        for(char j = i; j < i+5; ++j){
            tempstr+=j;
        }
        int id(std::rand()%10000);
        if(id >= 9000){
            id = 1234;
        }
        myvect.push_back(Fax(tempstr, id));
    }

    //чтение
    std::cout << "Vector, not sorted:\n";
    reading_iter(myvect);

    //сортировка
    std::sort(myvect.begin(), myvect.end(), comp);
    std::cout << "Vector, sorted descending:\n";
    reading_iter(myvect);

    //поиск
    auto cmp_asc(
        [](const Fax& first,const Fax& second){
            return first < second;
    });
    std::sort(myvect.begin(), myvect.end(), cmp_asc);

    std::cout << "Finding fax with id = 1234 in vector: ";
    Fax fax("Fax", 1234);
    if(std::binary_search(myvect.begin(), myvect.end(), fax)){
        std::cout << "Found!\n";
    } else{
        std::cout << "Not found!\n";
    }

    std::stack<Fax> mystack;
    std::cout << "Finding faxes with id > 5000 and copying them into stack\nStack:\n";
    copy_if(myvect, mystack, Fax("Fax1", 5000), comp);
    reading_stack(mystack);

    std::cout << "Stack, sorted ascending\n";
    sort_stack(mystack, cmp_asc);
    reading_stack(mystack);

    std::cout << "Vector, sorted ascending\n";
    reading_iter(myvect);

    std::list<Fax> mylist;
    merge(myvect, mystack, mylist);

    std::cout << "List, merged from stack and vector\n";
    reading_iter(mylist);

    std::cout << "Faxes with id devided by 5 in list: " << std::count_if(mylist.begin(), mylist.end(), [](const Fax& elem){return elem.get_id() % 5 == 0;}) << "\n";
    std::cout << "List had fax with id < 1000: ";
    if(std::count_if(mylist.begin(), mylist.end(), [](const Fax& elem){return elem.get_id() < 1000;})){
        std::cout << "YES\n";
    } else{
        std::cout << "NO\n";
    }
}
