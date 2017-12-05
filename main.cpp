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
    if (testExpression.devariablize(&mainCalc) == 1) cout << "Syntax error - undefined variable\n";
    testExpression.print();
    testExpression.dropBorders();
    testExpression.print();
    return 0;
}