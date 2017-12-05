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
    cout << "testExpression.value: " << testExpression.getValue() <<endl;
    Node* testTree = testExpression.parse(&mainCalc);
    testTree->print();
    return 0;
}