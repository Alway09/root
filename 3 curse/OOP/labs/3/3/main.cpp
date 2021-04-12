#include<iostream>
#include<cstddef>
#include"righttriangle.h"

class TestClass{
    public:
        TestClass(char c = '0') : m_c(c){}
        ~TestClass(){}

        char get() const{
            return m_c;
        }

    private:
        char m_c;
};

int main(){
    size_t n = 5;
    RightTriangle<double> obj1(n);
    obj1.set_at(3, 4, 8);
    obj1.set_at(1, 3, 2);
    obj1.set_at(5, 5, 5);

    std::cout << "obj1:" << "\n";
    for(size_t i = 1; i <= n; ++i){
        for(size_t j = 1; j <= n; ++j){
            if(i <= j){
                std::cout << obj1.get_at(i, j);
            } else{
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    n = 8;
    RightTriangle<TestClass> obj2(n);
    obj2.set_at(3, 7, TestClass('a'));
    obj2.set_at(1, 1, TestClass('g'));
    obj2.set_at(4, -6, TestClass('t'));
    obj2.set_at(5, 5, TestClass('v'));

    std::cout << "\nobj2:" << "\n";
    for(size_t i = 1; i <= n; ++i){
        for(size_t j = 1; j <= n; ++j){
            if(i <= j){
                std::cout << obj2.get_at(i, j).get();
            } else{
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
