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
//#include "CCparser.h"
#include "CCalculator.h"
//#include "CInteger.h"
//#include "CLongInteger.h"
//#include "CDecimal.h"

using namespace std;


int main()
{

    CCalculator calc;
    calc.run();

//    cout << setw(9) << setfill('0') << 448598 << endl;


    return 0;
}


//todo list
//-input validation

//((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1))