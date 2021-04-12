#include<iostream>
#include<string>

class PrintDevise{
    public:
        PrintDevise(){}
        virtual ~PrintDevise(){}

        virtual void print() const = 0;
        virtual std::string get_info() const = 0;
};

class Printer : public PrintDevise{
    public:
        Printer(std::string name = "Printer") : PrintDevise(), m_name(name){}
        ~Printer(){}

        void print() const override { std::cout << m_name << " is printing\n"; }
        std::string get_info() const override { return m_name; }

    private:
        std::string m_name;
};

class Fax : public PrintDevise{
    public:
        Fax(std::string name = "Fax") : PrintDevise(), m_name(name){}
        ~Fax(){}

        void print() const override { std::cout << m_name << " is printing\n"; }
        std::string get_info() const override { return m_name; }

        virtual std::string send_data(){ std::cout << m_name << " is sending data\n"; }
        virtual void get_data(){ std::cout << m_name << " is getting data\n"; }

    private:
        std::string m_name;
};

void print_info(PrintDevise* device){
    std::cout << device->get_info() << "\n";
}

int main(){
    PrintDevise* parent = new Printer("Printer 1");

    print_info(parent);
    parent->print();

    Fax fax(std::string("Fax 1"));
    delete parent;
    parent = &fax;

    std::cout << "\n";
    print_info(parent);
    parent->print();
    fax.get_data();
    fax.send_data();
    std::cout << "\n";
}