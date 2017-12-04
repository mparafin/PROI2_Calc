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

int Expression::devariablize(Calculator* calc){ //podmienienie zmiennych na wyrażenia
    /* Funkcja podmienia zmienne danego kalkulatora znajdujące się w wyrażeniu na ich definicje, dopóki nie znajdzie już żadnej zdefiniowanej zmiennej.
    *Funkcja zwraca 0 jeśli operacja zakończyła się powodzeniem.
    *
    */

    vector<Variable> definedVariables = calc->getDefinedVariables();
    int emptyRuns = 0;
    while(emptyRuns != definedVariables.size() ){ //próbuj podmienić wszystkie zmienne tyle razy, aż żadna nie zostanie znaleziona
        emptyRuns = 0;
        for(int i=0; i < definedVariables.size(); i++) {
            size_t position = value.find(definedVariables[i].name); //position = początek nazwy zmiennej
            if(position != string::npos) value.replace( position, position + definedVariables[i].name.size(), definedVariables[i].definition.value); //podmień nazwę na definicję
            else emptyRuns++;
        }
    }
    
    //w tym momencie mamy podmienione wszystkie zmienne, jakie są zdefiniowane

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
    else return 1;    
}

int Expression::dropBrackets() { //opuść skrajne nawiasy, jeśli są
    
    if(*(this->value.begin()) != '(' ) return 0; //sukces, jeżeli nie zaczyna się od nawiasu
    else
    {
        int bracketDepth = 1;
        string::iterator i = value.begin()+1;
        while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
            if( *i == '(' ) bracketDepth++;
            if( *i == ')' ) bracketDepth--;
            i++;
        }
        if(i == value.end()-1 ) value = value.substr(1, value.size()-2 ); //jeżeli zamknięcie pierwszego to ostatni znak, usuń skrajne znaki
        return 0;
    }
}

Node* Expression::parse(Calculator *calc){

    if(devariablize(calc) == 1 ) {
        cout << "Syntax error!" << endl;
        return NULL;
    }
    
    dropBrackets();

}