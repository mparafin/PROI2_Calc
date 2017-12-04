#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__

#include <string>
#include "Node.hpp"

struct Calculator;

class Expression: public Node{
    private:
        std::string value;
    public:
        Expression(std::string);
        void print(); //wypisuje string value na ekran
        std::string getValue(); //zwraca value w postaci czystego stringa
        double calculate(); //pusta funkcja, Expression nigdy nie będzie występować w finalnym drzewie
        Node* parse(Calculator*); //interpretuje string value i tworzy poddrzewo tego wyrażenia

        int devariablize(Calculator*); //podmienia zmienne na wyrażenia, które je opisują
        int dropBrackets(); //usuwa skrajne nawiasy, jeżeli całe wyrażenie jest w nawiasie
};

#endif