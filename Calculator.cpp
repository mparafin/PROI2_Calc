#include "Calculator.hpp"
#include "Node.hpp"
#include "Expression.hpp"
#include <iostream>

using namespace std;

void Calculator::defineVariable(string& input_name, string& input_definition){
    defined_variables.push_back(Variable(input_name, input_definition));
}

void Calculator::memoryClear(){ defined_variables.clear(); }

void Calculator::print(){
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        defined_variables[i].definition.print();
        cout << endl;
    }
}

void Calculator::calculate(){
    Node* temp = NULL;
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        temp = defined_variables[i].definition.parse();
        cout << temp->calculate() << endl;
    }
}