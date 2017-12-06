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

void Expression::print(int depth){
    for(int i=0; i<depth; i++) cout << "|";
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

    size_t found = value.find_first_not_of("1234567890. +-*^/!()"); //znalezienie pierwszego znaku który nie jest liczbą lub operatorem matematycznym
    if(found == string::npos) return 0; //sukces jeśli brak zmiennych na samym początku

    while(1){ //pętla testująca czy znaleziony znak nie jest funkcją jednoargumentową (exp, ln, log)
        if(value[found] == 'e' && value[found+1] == 'x' && value[found+2] == 'p' && value[found+3] == '(') {
            found = value.find_first_not_of("1234567890. +-*^/!()", found+3);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'n' && value[found+2] == '('){
            found = value.find_first_not_of("1234567890. +-*^/!()", found+2);
            continue;
        }
        if(value[found] == 'l' && value[found+1] == 'o' && value[found+2] == 'g' && value[found+3] == '('){
            found = value.find_first_not_of("1234567890. +-*^/!()", found+3);
            continue;
        }
        break;
    }
    if(found == string::npos) return 0; //sukces jeśli brak zmiennych po uwzględnieniu funkcji
    else return 1;    
}

int Expression::dropBorders() { //opuść skrajne nawiasy i usuń spacje, jeśli są
    
    //usunięcie spacji:
    string::iterator i = value.begin();
    while(i != value.end() ){
        if(*i == ' ') value.erase(i);
        i++;
    }

    //usunięcie skrajnych nawiasów:
    
    int bracketDepth = 0;
    i = value.begin()-1;
    while(i != value.end()){ //licz nawiasy aż nie zamkniesz pierwszego
        i++;
        if( *i == '(' ) bracketDepth++;
        if( *i == ')' ) bracketDepth--;
    }
    if(bracketDepth > 0) return 2; // za mało nawiasów
    if(bracketDepth < 0) return 1; // za dużo nawiasów

    else { 
        if( *(value.begin()) == '(' && *(value.end()-1) == ')' ){ //jeżeli pierwszy i ostatni znak to nawiasy, usuń skrajne znaki
            value.erase( value.begin() );
            value.erase( value.end()-1 );
            dropBorders(); //na wypadek gdyby był przypadek "((...))"
        }
        return 0;
    }
    
}

Node* Expression::parse(Calculator *calc){ //GŁÓWNA FUNCKJA TEGO PROGRAMU

    //Przygotowanie stringa
    if(devariablize(calc) == 1 ) { //podstawienie wyrażeń za zmienne i kontrola składni
        cout << "Syntax error!" << endl;
        return NULL;
    }
    switch(dropBorders()){ // usunięcie skrajnych nawiasów i spacji
        case 1:
            cout << "Too many brackets!\n";
            return NULL;
            break;
        case 2:
            cout << "Too little brackets!\n";
            return NULL;
            break;
    }
    //W tym momencie mamy czyste wyrażenie do parsowania

    int head = 0;
            //cout << "huh?\n";

    //szukaj plusa/minusa aż znajdziesz lub skończy się value:
    for (head=value.size(); head > -1; head--) {

        if (value[head] == '+' || value[head] == '-') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if(value[head] == '+' || value[head] == '-'){ //jeżeli znalazł plusa/minusa nie w nawiasie

        Node* newNode = new Twoarg_op(value.substr(head, 1), value.substr( 0, head), value.substr(head+1));
        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora plus/minus
    }

    //szukaj mnożenia/dzielenia aż znajdziesz lub skończy się value:
    for (head=value.size(); head > -1; head--) {

        if (value[head] == '*' || value[head] == '/') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if(value[head] == '*' || value[head] == '/'){ //jeżeli znalazł mnożenie/dzielenie nie w nawiasie
        Node* newNode = new Twoarg_op(value.substr(head, 1), value.substr( 0, head), value.substr(head+1));

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora mnożenia/dzielenia
    }


    //szukaj potęgowania aż znajdziesz lub skończy się value:
    for (head=value.size(); head > -1; head--) {

        if (value[head] == '^') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if(value[head] == '^'){ //jeżeli znalazł potęgowanie nie w nawiasie
        Node* newNode = new Twoarg_op(value.substr(head, 1), value.substr( 0, head), value.substr(head+1));

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora potęgowania
    }


    //szukaj wyrażenia log()
    for (head=value.size(); head > -1; head--) {

        if (value[head] == 'l' && value[head+1] == 'o' && value[head+2] == 'g' && value[head+3] == '(') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if (value[head] == 'l' && value[head+1] == 'o' && value[head+2] == 'g' && value[head+3] == '(') {
            Node* newNode = new Onearg_op(value.substr(head, 3), value.substr(head+3));

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora log()
    }


    //szukaj wyrażenia ln()
    for (head=value.size(); head > -1; head--) {

        if (value[head] == 'l' && value[head+1] == 'n' && value[head+2] == '(') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if (value[head] == 'l' && value[head+1] == 'n' && value[head+2] == '(' ) {
            Node* newNode = new Onearg_op(value.substr(head, 2), value.substr(head+2));

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora ln()
    }



    //szukaj wyrażenia exp()
    for (head=value.size(); head > -1; head--) {

        if (value[head] == 'e' && value[head+1] == 'x' && value[head+2] == 'p' && value[head+3] == '(') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if (value[head] == 'e' && value[head+1] == 'x' && value[head+2] == 'p' && value[head+3] == '(') {
            Node* newNode = new Onearg_op(value.substr(head, 3), value.substr(head+3));

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora log()
    }


    //szukaj silni aż znajdziesz lub skończy się value:
    for (head=value.size(); head > -1; head--) {

        if (value[head] == '!') { head--; break;}

        if(value[head] == ')'){ //pominięcie nawiasów
            int bracketDepth = 1;
            head--;
            while(bracketDepth != 0){ //licz nawiasy aż nie zamkniesz pierwszego
                if( value[head] == ')' ) bracketDepth++;
                if( value[head] == '(' ) bracketDepth--;
                head--;
            }
            head++;
        }
    }
    head++;

    if(value[head] == '!'){ //jeżeli znalazł potęgowanie nie w nawiasie
        Node* newNode = new Onearg_op(value.substr(head, 1), value.substr( 0, head) );

        newNode = newNode->parse(calc);
        return newNode; // zwróć wskaźnik do nowego poddrzewa zaczynającego się od operatora potęgowania
    }


    //if all else fails - stwórz z siebie Argument
    Node* newNode = new Argument( atof( value.c_str() ));
    return newNode;
}