#include <iostream>
#include <string>
#include "Calculator.hpp"

using namespace std;

int main(){
    Calculator mainCalc;
    cout << "Yay!" << endl;
    cout << "Podaj input:\n";
    string buffer;
    cin >> buffer;
    Expression testExpression(buffer);
    testExpression.print();
    testExpression.dropBrackets();
    cout << "After testExpression.dropBrackets(): ";
    testExpression.print();
    //cout << testExpression.print() << endl;
    return 0;
}