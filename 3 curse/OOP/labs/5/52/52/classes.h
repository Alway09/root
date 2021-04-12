#ifndef CLASSES_H
#define CLASSES_H

#include<iostream>
#include<string>

class PrintDevise{
    public:
        PrintDevise(){}
        virtual ~PrintDevise(){}

        virtual void print() const = 0;
        virtual std::string get_info() const = 0;
};

class Fax : public PrintDevise{
    public:
        Fax(std::string name = "Fax") : PrintDevise(), m_name(name){}
        ~Fax(){}

        void print() const override { std::cout << m_name << " is printing\n"; }
        std::string get_info() const override { return m_name; }

        friend std::ostream& operator<<(std::ostream& out, const Fax& elem);
        void rename(std::string name){ m_name = name; }
        void send_data(){ std::cout << m_name << " is sending data\n"; }
        void get_data(){ std::cout << m_name << " is getting data\n"; }

    private:
        std::string m_name;
};

std::ostream& operator<<(std::ostream& out, const Fax& elem){
    out << elem.get_info();
    return out;
}


#endif // CLASSES_H
