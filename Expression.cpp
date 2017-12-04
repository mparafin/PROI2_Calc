#include "Expression.hpp"
#include "Calculator.hpp"
#include <string>
#include <iostream>

using namespace std;

Expression::Expression(string input): value(input){};

void Expression::print(){
    cout << value << endl;
}

string Expression::getValue(){ return value; }

double Expression::calculate(){}

int Expression::devariablize(Calculator calc){ //podmienienie zmiennych na wyrażenia
    /* Funkcja podmienia zmienne danego kalkulatora znajdujące się w wyrażeniu na ich definicje, dopóki nie znajdzie już żadnej zdefiniowanej zmiennej.
    *Funkcja zwraca 0 jeśli operacja zakończyła się powodzeniem.
    *
    */

    vector<Variable> definedVariables = calc.getDefinedVariables();
    

    size_t found = value.find_first_not_of("123456789 +-*/^!()"); //znalezienie pierwszego znaku który nie jest liczbą lub operatorem matematycznym
    if(value[found] == string::npos) return 0; //sukces jeśli brak zmiennych na samym początku

    while(1){ //pętla testująca czy znaleziony znak nie jest funkcją jednoargumentową (exp, ln, log)
        if(value[found] == 'e' && value[found+1] == 'x' && value[found+2] == 'p' && value[found+3] == '(') {
            found = value.find_first_not_of("123456789 +-*/^!()", found+3);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'n' && value[found+2] == '('){
            found = value.find_first_not_of("123456789 +-*/^!()", found+2);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'o' && value[found+2] == 'g' && value[found+3] == '('){
            found = value.find_first_not_of("123456789 +-*/^!()", found+3);
            continue;
        }
        break;
    }
    if(value[found] == string::npos) return 0; //sukces jeśli brak zmiennych po uwzględnieniu funkcji

    size_t start = found;
    found = value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890");
    string found_name = value.substr(start, found-start);

    
}

Node* Expression::parse(Calculator calc){

    devariablize(calc);
    dropBrackets();

    if(*(this->value.begin()) == '(' ){
        int bracketCounter = 0;
        for(string::iterator it=value.begin(); it != value.end(); it++){

        }
    }
}

int Expression::dropBrackets() {
    return 1;  //TODO implement
}