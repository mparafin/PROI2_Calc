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
    cout << buffer << endl;
    mainCalc.defineVariable("a", "10");
    value = mainCalc.getVariableDefinition("a");
    cout << "value: " << value << endl;
    Expression testExpression(buffer);
    testExpression.dropBrackets();
    testExpression.print();
    testExpression.devariablize(&mainCalc);
    testExpression.print();
    return 0;
}