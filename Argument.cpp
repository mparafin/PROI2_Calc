#include "Argument.hpp"
#include <iostream>

Argument::Argument(double input_value): value(input_value){}

void Argument::print(){ std::cout << value << std::endl; }

Node* Argument::parse(Calculator* calc){ return this; }

double Argument::calculate(){ return value; }