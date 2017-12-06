#include "Onearg_op.hpp"
#include "Expression.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Onearg_op::Onearg_op(string type_indicator, string argument){
    if(type_indicator == "-") type = MINUS;
    else if(type_indicator == "exp") type = EXP;
    else if(type_indicator == "ln") type = LN;
    else if(type_indicator == "log") type = LOG;
    else if(type_indicator == "!") type = STRONG;
    arg = new Expression(argument);
}

Onearg_op::~Onearg_op(){
    delete arg;
    delete &arg;
}

void Onearg_op::print(int depth){
    for(int i=0; i<depth; i++) cout << "|";
    switch(type){
        case MINUS: cout << "-(\n"; for(int i=0; i<depth; i++) cout << "|"; cout << "(\n"; break;
        case EXP: cout << "exp(\n"; for(int i=0; i<depth; i++) cout << "|"; cout << "(\n"; break;
        case LN: cout << "ln\n"; for(int i=0; i<depth; i++) cout << "|"; cout << "(\n"; break;
        case LOG: cout << "log\n"; for(int i=0; i<depth; i++) cout << "|"; cout << "(\n"; break;
        case STRONG: cout << "!\n"; for(int i=0; i<depth; i++) cout << "|"; cout << "(\n"; break;
    }
    arg->print(depth+1);
    for(int i=0; i<depth; i++) cout << "|";
    cout << ")\n" << endl;
}

Node* Onearg_op::parse(Calculator* calc){
    Node* temp = arg;
    arg = temp->parse(calc);
    delete temp;
    return this;
}


double Onearg_op::calculate(){
    switch(type){
        case MINUS: return (-1)*arg->calculate();
        case EXP: return exp(arg->calculate());
        case LN: return log(arg->calculate());
        case LOG: return log10(arg->calculate());
        case STRONG:
            double k = arg->calculate();
            if (floor(abs(k)) != abs(k)){
                cout << "ERROR: argument of \"strong\" not integer\n";
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