#include<iostream>
#include<cstddef>
#include"righttriangle.h"

class TestClass{
    public:
        TestClass(int num = 0) : m_num(num){}
        ~TestClass(){}

        int get() const{
            return m_num;
        }

    private:
        int m_num;
};

int main(){
    size_t n = 5;
    RightTriangle<double> obj1(n);
    obj1[2][3] = 8;
    obj1[0][2] = 2;
    obj1[4][4] = 5;
    obj1[2][0] = 3;
    obj1[2][3] = 7;

    std::cout << "obj1:" << "\n";
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(i <= j){
                std::cout << obj1[i][j];
            } else{
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    n = 8;
    RightTriangle<TestClass> obj2(n);
    obj2[2][6] = TestClass(8);
    obj2[0][0] = TestClass(4);
    obj2[3][5] = TestClass(1);
    obj2[6][6] = TestClass(7);
    obj2[5][6] = TestClass(3);
    obj2[2][3] = TestClass(2);

    std::cout << "\nobj2:" << "\n";
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(i <= j){
                std::cout << obj2[i][j].get();
            } else{
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
