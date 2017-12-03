#include "Expression.hpp"
#include <string>
#include <iostream>

using namespace std;

Expression::Expression(string input): value(input){};

void Expression::print(){
    cout << value << endl;
}

double Expression::calculate(){}

Node* Expression::parse(){
    
}