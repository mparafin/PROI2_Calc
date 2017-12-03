#include "Argument.hpp"
#include <iostream>

Argument::Argument(double input_value): value(input_value){}

void Argument::print(){ std::cout << value << std::endl; }

double Argument::calculate(){ return value; }