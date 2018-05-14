/************************************************************
 *              ENDLESS PRECISION CALCULATOR                *
 *                                                          *
 *            Author: Victor Kataev                         *
 *            Mentors: Josef Vogel, Klara Schovankova       *
 ************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
#include <typeinfo>
#include <unordered_map>
#include "COperand.h"
#include "CCparser.h"
#include "CCalculator.h"
#include "CInteger.h"
#include "CLongInteger.h"
#include "CDecimal.h"

using namespace std;


int main()
{

//    COperand * p = new CVariable("sdfk", "349");
//    COperand * p1 = new CDecimal("349");
//
//    cout << typeid(*p1).name();

//    string sinput("53.345747");
//    string::size_type sz;
//    double dinput = stod(sinput);
//
//    cout << dinput;
//
//    do
//    {
//        getline(cin, input, '\n');
//        cout << input << endl;
//        extractInt(input);
//
//    } while(input != "quit");
//
//
    CCalculator calc;
    calc.run();

    return 0;
}


//todo list
//input validation
//((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1))