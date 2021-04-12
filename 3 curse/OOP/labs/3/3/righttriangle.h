#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include<cstddef>
#include<iostream>

template<class T>
class RightTriangle{
    public:
        RightTriangle(int n = 2);
        ~RightTriangle(){ if(m_triangle){ delete[] m_triangle; } }

        T get_at(int i, int j) const;
        void set_at(int i, int j,const T& elem);

    private:
        int m_n;
        T* m_triangle;
};

template<class T>
RightTriangle<T>::RightTriangle(int n) : m_n(n), m_triangle(nullptr){
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
T RightTriangle<T>::get_at(int i, int j) const{
    --i; --j;

    try{
        if(i > j || (i >= m_n && j >= m_n) || i < 0 || j < 0) throw(1);

        size_t n(m_n), pol(0);
        --n;

        while(i){
            pol += n;
            --n; --i;
        }
        pol += j;

        return m_triangle[pol];
    }
    catch(int){
        std::cout << "RightTriangle<T>::get_at(int i, int j)::Index out of range\n";
        exit(1);
    }
}

template<class T>
void RightTriangle<T>::set_at(int i, int j,const T& elem){
    --i; --j;

    try{
        if(i > j || (i >= m_n && j >= m_n) || i < 0 || j < 0) throw(1);

        size_t n(m_n), pol(0);
        --n;

        while(i){
            pol += n;
            --n; --i;
        }
        pol += j;

        m_triangle[pol] = elem;
    }
    catch(int){
        std::cout << "RightTriangle<T>::set_at(int i, int j,const T& elem)::Index out of range\n";
        exit(1);
    }
}

#endif // RIGHTTRIANGLE_H
