#include <iostream>
#include <string>
#include "Calculator.hpp"

using namespace std;

int main(){
    Calculator mainCalc;
    cout << "Yay!" << endl;
    cout << "Podaj input:\n";
    string buffer, key, value;
    getline(cin, buffer);
    mainCalc.defineVariable("a", "10");
    mainCalc.defineVariable("b", "a+5");
    Expression testExpression(buffer);
    Node* testTree = testExpression.parse(&mainCalc);
    if (testTree == NULL) cout << "ABANDON SHIP\n";
    else {
        testTree->print(0);
        cout << "Wynik: " << testTree->calculate() << endl;
    }
    return 0;
}