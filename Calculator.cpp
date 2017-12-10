#include "Calculator.hpp"
#include "Node.hpp"
#include "Expression.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Calculator::defineVariable(string input_name, string input_definition){
    defined_variables.push_back(Variable(input_name, input_definition));
}

bool Calculator::checkVariable(string input){ 
    for(int i=0; i<defined_variables.size(); i++){
        if(defined_variables[i].name == input) return 1; //zwraca 1, jeśli zmienna jest już zdefiniowana
    }
    return 0; //zwraca 0, jeśli zmienna nie jest zdefiniowana
}

string Calculator::getVariableDefinition(string key){ //zwraca definicję zmiennej w postaci stringa
    for(int i=0; i<defined_variables.size(); i++){
        if(defined_variables[i].name == key) return defined_variables[i].definition.getValue();
    }
}

void Calculator::memoryClear(){ defined_variables.clear(); }

void Calculator::print(){
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        defined_variables[i].definition.print(0);
        cout << endl;
    }
}

void Calculator::calculate(){
    Node* temp = NULL;
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        temp = defined_variables[i].definition.parse(this);
        cout << temp->calculate() << endl;
    }
}

void Calculator::interface(){
    string buffer, key, value;
    cout << "Podaj input:\n";
    getline(cin, buffer);

    if(buffer.find("=") == string::npos) { //oblicz pojedyncze wyrażenie
        Expression currentExpression(buffer);
        Node* currentCalculationTree = currentExpression.parse(this);
        if(currentCalculationTree == NULL)  cout << "ABANDON SHIP\n";
        else cout << "Wynik: " << currentCalculationTree->calculate() << endl;
        return;
    }
    
}