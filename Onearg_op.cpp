#include "Onearg_op.hpp"
#include "Expression.hpp"
#include <iostream>
#include <cmath>

Onearg_op::Onearg_op(std::string& type_indicator, std::string& argument){
    if(type_indicator == "-") type = MINUS;
    else if(type_indicator == "exp") type = EXP;
    else if(type_indicator == "ln") type = LN;
    else if(type_indicator == "log") type = LOG;
    else if(type_indicator == "!") type = STRONG;
    Expression* temp = new Expression(argument);
    arg = temp->parse();
}

Onearg_op::~Onearg_op(){
    delete arg;
    delete &arg;
}

void Onearg_op::print(){
    switch(type){
        case MINUS: std::cout << "-\n(\n"; break;
        case EXP: std::cout << "exp\n(\n"; break;
        case LN: std::cout << "ln\n(\n)"; break;
        case LOG: std::cout << "log\n(\n)"; break;
        case STRONG: std::cout << "!\n(\n)"; break;
    }
    arg->print();
    std::cout << ")";
}


double Onearg_op::calculate(){
    switch(type){
        case MINUS: return (-1)*arg->calculate();
        case EXP: return exp(arg->calculate());
        case LN: return log(arg->calculate());
        case LOG: return log10(arg->calculate());
        case STRONG:
            double k = arg->calculate();
            if (std::floor(std::abs(k)) != std::abs(k)){
                std::cout << "ERROR: argument of \"strong\" not integer\n";
                return 0;
            }
            else{
                int n=1;
                for(int i=1; i<k; i++) n *= i;
                return n;
            }
            break;
    }
}