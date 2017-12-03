#include "Onearg_op.hpp"
#include "Expression.hpp"
#include <iostream>
#include <cmath>

Onearg_op::Onearg_op(std::string& indicator, std::string& argument){
    if(indicator == "-") type = MINUS;
    else if(indicator == "exp") type = EXP;
    else if(indicator == "ln") type = LN;
    else if(indicator == "log") type = LOG;
    else if(indicator == "!") type = STRONG;
    arg = new Expression(argument);
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
                for(int i=1; i<k; i++) k *= i;
                return k;
            }
            break;
    }
}