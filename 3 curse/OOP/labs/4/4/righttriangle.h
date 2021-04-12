#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include<cstddef>
#include<iostream>

template<class T>
class RightTriangle{
    private:
    class SubClass{
        public:
            SubClass(T* pointer, size_t i, size_t n);
            ~SubClass(){};

            T& operator[](size_t index) const;

        private:
            T* m_ptr;
            size_t m_index;
            size_t m_n;
    };

    public:
        RightTriangle(size_t n = 0);
        ~RightTriangle(){ if(m_triangle){ delete[] m_triangle; } }

        T get_at(size_t i, size_t j) const;
        void set_at(size_t i, size_t j,const T& elem);

        RightTriangle<T>::SubClass& operator[](size_t index) const;

    private:        
        size_t m_n;
        T* m_triangle;
};

template<class T>
RightTriangle<T>::RightTriangle(size_t n) : m_n(n), m_triangle(nullptr){
    try{
        if(n <= 1) throw(1);

        u_int amount(0);
        while(n){
            amount += n;
            --n;
        }

        m_triangle = new T[amount]();
    }
    catch(int){
        std::cout << "RightTriangle<T>::RightTriangle(int n)::Uncorrect size" << "\n";
        exit(1);
    }
    catch(std::bad_alloc){
        std::cout << "RightTriangle<T>::RightTriangle(int n)::Failed to allocate memory" << "\n";
        exit(1);
    }
}

template<class T>
RightTriangle<T>::SubClass::SubClass(T* pointer, size_t i, size_t n) : m_ptr(pointer), m_index(i), m_n(n){}

template<class T>
T& RightTriangle<T>::SubClass::operator[](size_t index) const{
    try {
        if(m_index > index || (m_index >= m_n && index >= m_n)) throw(1);

        return m_ptr[index];
    }
    catch (int) {
        std::cout << "RightTriangle<T>::operator[]::Index out of range\n";
        exit(1);
    }
}

template<class T>
typename RightTriangle<T>::SubClass& RightTriangle<T>::operator[](size_t index)const{
    T* ptr = m_triangle;
    size_t i = index;
    size_t n(m_n);
    --n;

    while(i){
        ptr += n;
        --n; --i;
    }

    SubClass* obj = new SubClass(ptr, index, m_n);
    return *obj;
}

#endif // RIGHTTRIANGLE_H
