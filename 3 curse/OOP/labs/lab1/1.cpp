#include<iostream>

class MyClass{
    public:
        MyClass() : m_data(0){ std::cout << "Constructor called\n"; }
        ~MyClass(){ std::cout << "Destructor called\n"; }

        void set_data(int data){ m_data = data; }
        int get_data(){ return m_data; }

    private:
        int m_data;
};

int main(){
    MyClass obj;

    obj.set_data(4);
    std::cout << obj.get_data() << "\n";
}