#ifndef __CALCULATOR__
#define __CALCULATOR__

#include "Expression.hpp"
#include <vector>
#include <string>

struct Variable{
    std::string name;
    Expression definition;
    Variable(std::string& key, std::string& value): name(key), definition(value){};
};

class Calculator{
    private:
        std::vector<Variable> defined_variables; //wektor zdefiniowanych zmiennych
    public:
        void defineVariable(std::string&, std::string&); //zdefiniowanie zmiennej
        void memoryClear(); //wyczyszczenie zbioru znanych zmiennych
        void print(); // wypisanie wszystkich zdefiniowanych zmiennych wraz z definicjami
        void calculate(); // policzenie wartości wszystkich zmiennych
};

#endif