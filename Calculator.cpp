#include "Calculator.hpp"

using namespace std;

void Calculator::defineVariable(string& input_name, string& input_definition){
    defined_variables.push_back(Variable(input_name, input_definition));
}

void Calculator::memoryClear(){ defined_variables.clear(); }