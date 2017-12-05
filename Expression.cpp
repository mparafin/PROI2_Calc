#include "Expression.hpp"
#include "Calculator.hpp"
#include "Onearg_op.hpp"
#include "Twoarg_op.hpp"
#include "Argument.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

Expression::Expression(string input): value(input){};

void Expression::print(){
    cout << this->value << endl;
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
            if(position != string::npos) value.replace( position, definedVariables[i].name.length(), "(" + definedVariables[i].definition.value + ")"); //podmień nazwę na definicję
            else emptyRuns++;
        }
    }
   
    //w tym momencie mamy podmienione wszystkie zmienne, jakie są zdefiniowane

    size_t found = value.find_first_not_of("1234567890 +-*^/!()"); //znalezienie pierwszego znaku który nie jest liczbą lub operatorem matematycznym
    if(found == string::npos) return 0; //sukces jeśli brak zmiennych na samym początku

    while(1){ //pętla testująca czy znaleziony znak nie jest funkcją jednoargumentową (exp, ln, log)
        if(value[found] == 'e' && value[found+1] == 'x' && value[found+2] == 'p' && value[found+3] == '(') {
            found = value.find_first_not_of("1234567890 +-*^/!()", found+3);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'n' && value[found+2] == '('){
            found = value.find_first_not_of("1234567890 +-*^/!()", found+2);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'o' && value[found+2] == 'g' && value[found+3] == '('){
            found = value.find_first_not_of("123456789 +-*^/!()", found+3);
            continue;
        }
        break;
    }
    if(found == string::npos) return 0; //sukces jeśli brak zmiennych po uwzględnieniu funkcji
    else return 1;    
}

void Expression::dropBorders() { //opuść skrajne nawiasy i spacje, jeśli są
    
    //usunięcie skrajnych spacji:
    if( *(value.begin()) == ' ') { value.erase( value.begin() ); dropBorders(); }
    if( *(value.end()-1) == ' ') { value.erase( value.end()-1 ); dropBorders(); }

    //usunięcie skrajnych nawiasów:
    if( *(value.begin()) != '(' ) return; //sukces, jeżeli nie zaczyna się od nawiasu
    else
    {
        int bracketDepth = 1;
        string::iterator i = value.begin()+1;
        while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
            if( *i == '(' ) bracketDepth++;
            if( *i == ')' ) bracketDepth--;
            i++;
        }
        if(i-1 == value.end()-1) { //jeżeli zamknięcie pierwszego to ostatni znak, usuń skrajne znaki
            value.erase( value.begin() );
            value.erase( value.end()-1 );
            dropBorders(); //na wypadek gdyby był przypadek "((...))"
        }
        else return;
    }
}

Node* Expression::parse(Calculator *calc){ //GŁÓWNA FUNCKJA TEGO PROGRAMU

    //Przygotowanie stringa

    if(devariablize(calc) == 1 ) { //podstawienie wyrażeń za zmienne
        cout << "Syntax error!" << endl;
        return NULL;
    }
    dropBorders(); // usunięcie skrajnych nawiasów i spacji

    //W tym momencie mamy czyste wyrażenie do parsowania

    int head = 0;

    //szukaj plusa/minusa aż znajdziesz lub skończy się value:
    while( (value[head] != '+' || value[head] != '-') && value[head] != *(value.end()-1) ) {
        cout << "value[head]: " << value[head] << ", value.end(): " << *(value.end()) << endl;
        if(value[head] == '('){ //pominięcie nawiasów
            int bracketDepth = 1;
            head++;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == '(' ) bracketDepth++;
                if( value[head] == ')' ) bracketDepth--;
                head++;
            }
        }
        head++;
    }
    head--;
    if(value[head] == '+' || value[head] == '-'){ //jeżeli znalazł plusa/minusa nie w nawiasie
        cout << "Znalazł plusa, head = " << head << ", value[head]: " << value[head] << endl;
        Node* newNode = new Twoarg_op(value.substr(head, head), value.substr( 0, head), value.substr(head+1));
        cout << "Stworzył new Twoarg_op: " << value.substr(head, head) << ", " << value.substr( 0, head) << ", " << value.substr(head+1) << endl;
        newNode->print();
        delete this;
        cout << "Usunął się\n";
        newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora plus/minus
    }

    //szukaj mnożenia/dzielenia aż znajdziesz lub skończy się value:
    while( (value[head] != '*' || value[head] != '/') && value[head] != *(value.end()) ) {
        if(value[head] == '('){ //pominięcie nawiasów
            int bracketDepth = 1;
            head++;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == '(' ) bracketDepth++;
                if( value[head] == ')' ) bracketDepth--;
                head++;
            }
        }
    }
    if(value[head] != '*' || value[head] != '/'){ //jeżeli znalazł mnożenie/dzielenie nie w nawiasie
        Node* newNode = new Twoarg_op(value.substr(head, head+1), value.substr( 0, head), value.substr(head+1));
        delete this;
        newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora plus/minus
    }


    //szukaj potęgowania aż znajdziesz lub skończy się value:
    while( value[head] != '^' && value[head] != *(value.end()) ) {
        if(value[head] == '('){ //pominięcie nawiasów
            int bracketDepth = 1;
            head++;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == '(' ) bracketDepth++;
                if( value[head] == ')' ) bracketDepth--;
                head++;
            }
        }
    }
    if(value[head] != '^'){ //jeżeli znalazł potęgowanie nie w nawiasie
        Node* newNode = new Twoarg_op(value.substr(head, head+1), value.substr( 0, head), value.substr(head+1));
        delete this;
        newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora plus/minus
    }



    //if all else fails - stwórz z siebie Argument
    Node* newNode = new Argument( atof( value.c_str() ));
    delete this;
    return newNode;
}