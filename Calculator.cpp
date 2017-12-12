#include "Calculator.hpp"
#include "Node.hpp"
#include "Expression.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Calculator::defineVariable(string input_name, string input_definition){
    for(int i=0; i<defined_variables.size(); i++){ //jeżeli zmienna jest już zdefiniowana, usuń
        if(input_name == defined_variables[i].name){
            defined_variables.erase(defined_variables.begin()+i);
        }
    }
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
    if(defined_variables.size() == 0) { cout << "No defined variables.\n"; return; }
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        defined_variables[i].definition.print(0);
    }
    return;
}

void Calculator::calculateSingleExpression(string input){ //oblicz pojedyncze wyrażenie
    Expression currentExpression(input);
    Node* currentCalculationTree = currentExpression.parse(this);
    if(currentCalculationTree != NULL) cout << "Result: " << currentCalculationTree->calculate() << endl;
    return;
}

void Calculator::calculateAll(){ //oblicz wyrażenia dla wszystkich zmiennych
    Node* temp = NULL;
    for(int i=0; i < defined_variables.size(); i++){
        cout << defined_variables[i].name << " = ";
        Expression tempExpression(defined_variables[i].definition.getValue());
        temp = tempExpression.parse(this);
        if(temp != NULL) cout << temp->calculate() << endl;
    }
    return;
}

int Calculator::interface(){
    /*Główny interfejs programu.
    Funkcja zwraca 1, jeśli chcemy powtórzyć wywołanie
    i 0, jeśli chcemy zakończyć działanie programu.*/
    
    string buffer, temp_key, temp_value;
    cout << "> ";
    getline(cin, buffer);

    if(buffer == "help" || buffer == "?") { cout << "A calculator with variables, standard operations (+, -, *, /, power, strong) and basic one-argument functions (exp, log, ln). Type in an expression to get the result or use the form \"<variable name> = <variable definition>\" to define new variables, which you will then be able to use in expressions.\n\nCommands:\nhelp, ?\t\t\tDisplay this text.\nexit, quit, q\t\tQuit the application.\nshow, print\t\tDisplay the defined variables.\ncalculate, all\t\tCalculate the values of all the defined variables.\n\n"; return 1; }
    if(buffer == "exit" || buffer == "quit" || buffer == "q") return 0;
    if(buffer == "show" || buffer == "print") { this->print(); return 1; }
    if(buffer == "calculate" || buffer == "all") { this->calculateAll(); return 1; }
    

    size_t equalSign = buffer.find("=");
    //jeżeli wyrażenie nie ma znaku równości lub zaczyna się od "=", to je oblicz
    if(equalSign == string::npos) { 
        this->calculateSingleExpression(buffer);
        return 1;
    }
    if(equalSign == 0){
        this->calculateSingleExpression(buffer.substr(1));
        return 1;
    }

    else{ //jeżeli jest "=", to po lewej jest nazwa zmiennej, a po prawej definicja
        temp_value = buffer.substr(buffer.find("=")+1); //weź prawą stronę jako definicję
        temp_key = buffer.substr(0, buffer.find("=")); //weź lewą stronę jako nazwę zmiennej

        //sprawdź, czy nazwa zmiennej jest poprawna, i ew. popraw:
        string::iterator i = temp_key.begin();
        while( *i != *temp_key.end() ) {  // usuń spacje
            if(*i == ' ') temp_key.erase(i);
            i++;
        }


        if(temp_key.find_first_not_of("1234567890_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos){
            cout << "Error: incorrect variable name\n";
            return 1;
        } // zwróc błąd, jeżeli nazwa zmiennej zawiera znaki niedozwolone, czyli cokolwiek poza literami, cyframi i "_"

        if(temp_key == "log" || temp_key == "ln" || temp_key == "exp"){
            cout << "Error: incorrect variable name (cannot be named as a function)\n";
            return 1;
        } //zwróć błąd, jeśli zmienna nazywa się tak samo jak funkcja
        



        //sprawdź pokrótce czy definicja nie zawiera czegoś niedozwolonego
        if(temp_value.find_first_not_of("1234567890. +-*^/!()abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Error: incorrect variable definition\n";
            return 1;
        }

        //sprawdź czy zmienna nie jest już zdefiniowana
        for(int i=0; i < defined_variables.size(); i++) {
            if(temp_key == defined_variables[i].name){
                cout << "Warning! Variable already defined:\n" << defined_variables[i].name << " = " << defined_variables[i].definition.getValue() << endl;
                cout << "Do you wish to redefine this variable? (Y/n): ";
                string answer;
                getline(cin, answer);
                if(answer == "no" || answer == "n") return 1;
            }
        }

        //sprawdź, czy nie ma rekurencji
        size_t position = 0;
        for(int i=0; i < defined_variables.size(); i++) {
            position = temp_value.find(defined_variables[i].name); //position = początek nazwy zmiennej
            if(position != string::npos && !isalnum( temp_value[ (position + defined_variables[i].name.length()) ] ) && temp_value[ (position + defined_variables[i].name.length()) ] != '_' ){
                if(defined_variables[i].definition.getValue().find(temp_key) != string::npos ) {
                    cout << "Error: variable recurrence\n";
                    return 1;
                }
            }
        }


        //jeśli wszystko w porządku, zdefiniuj nową zmienną
        defineVariable(temp_key, temp_value);
        cout << "Added new variable:\n" << "Name: '" << temp_key << "', definition: '" << temp_value << "'\n";
        return 1;
    }
}
