#include "Argument.hpp"
#include <iostream>

Argument::Argument(double input_value): value(input_value){}

void Argument::print(int depth){ 
    for(int i=0; i<depth; i++) std::cout << "|";
    std::cout << value << std::endl;
}

Node* Argument::parse(Calculator* calc){ return this; }

double Argument::calculate(){ return value; }