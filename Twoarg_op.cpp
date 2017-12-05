#include "Twoarg_op.hpp"
#include "Expression.hpp"
#include <iostream>
using namespace std;

Twoarg_op::Twoarg_op(string type_indicator, string left_arg, string right_arg){
    if(type_indicator == "+") type = PLUS;
    else if(type_indicator == "-") type = MINUS;
    else if(type_indicator == "/") type = DIVIDE;
    else if(type_indicator == "*") type = MULTIPLY;
    else if(type_indicator == "^") type = POWER;
    arg_left = new Expression(left_arg);
    arg_right = new Expression(right_arg);
}

Twoarg_op::~Twoarg_op(){
    delete arg_left;
    delete arg_right;
    delete &arg_left;
    delete &arg_right;
}

void Twoarg_op::print(){
    arg_left->print();
    switch(type){
        case PLUS: cout << "+\n"; break;
        case MINUS: cout << "-\n;"; break;
        case MULTIPLY: cout << "*\n"; break;
        case DIVIDE: cout << "/\n"; break;
    }
    arg_right->print();
}

Node* Twoarg_op::parse(Calculator* calc){
    arg_left = arg_left->parse(calc);
    arg_right = arg_right->parse(calc);
}

double Twoarg_op::calculate(){
    switch(type){
        case PLUS: return arg_left->calculate() + arg_right->calculate();
        case MINUS: return arg_left->calculate() - arg_right->calculate();
        case MULTIPLY: return arg_left->calculate() * arg_right->calculate();
        case DIVIDE: return arg_left->calculate() / arg_right->calculate();
    }
}