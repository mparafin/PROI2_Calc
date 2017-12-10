#include <iostream>
#include <string>
#include <cmath>
#include "Calculator.hpp"

using namespace std;

int main(){
    Calculator mainCalc;
    cout << "Yay!" << endl;
    mainCalc.defineVariable("a", "10");
    mainCalc.defineVariable("aa", "20");
    mainCalc.defineVariable("b", "a+5");

    mainCalc.interface();
    return 0;
}