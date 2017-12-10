#include <iostream>
#include <string>
#include <cmath>
#include "Calculator.hpp"

using namespace std;

int main(){
    cout << "Projekt2 - Kalkulator.\nAutor: Michał Parafiniuk, Copyright: Politechnika Warszawska\n\nType 'help' or '?' for help.\nInput: " << endl;
    Calculator mainCalc;
    while( mainCalc.interface() );
    return 0;
}