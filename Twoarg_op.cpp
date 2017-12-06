#include "Twoarg_op.hpp"
#include "Expression.hpp"
#include <iostream>
#include <math.h>
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

void Twoarg_op::print(int depth){
    arg_left->print(depth+1);
    for(int i=0; i<depth; i++) cout << "|";
    switch(type){
        case PLUS: cout << "+\n"; break;
        case MINUS: cout << "-\n"; break;
        case MULTIPLY: cout << "*\n"; break;
        case DIVIDE: cout << "/\n"; break;
        case POWER: cout << "^\n"; break;
    }
    arg_right->print(depth+1);
}

Node* Twoarg_op::parse(Calculator* calc){
    Node* temp = arg_left->parse(calc);
    delete arg_left;
    if (temp == NULL) return NULL;
    else arg_left = temp;
    
    temp = arg_right->parse(calc);
    delete arg_right;
    if (temp == NULL) return NULL;
    else arg_right = temp;
    return this;
}

double Twoarg_op::calculate(){
    switch(type){
        case PLUS: return arg_left->calculate() + arg_right->calculate();
        case MINUS: return arg_left->calculate() - arg_right->calculate();
        case MULTIPLY: return arg_left->calculate() * arg_right->calculate();
        case DIVIDE: return arg_left->calculate() / arg_right->calculate();
        case POWER: return pow( arg_left->calculate() , arg_right->calculate() );
    }
}