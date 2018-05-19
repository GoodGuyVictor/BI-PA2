#include <vector>
#include <iostream>
#include <stack>
#include "CVariable.h"
#include "CExpression.h"
#include "Enums.h"

using namespace std;

class CCalculator
{
private:
    vector<CVariable>   m_variables;
    vector<string>      m_history;

    string          readInput               ();
    void            removeWhiteSpaces       (string &);
    void            createNewVariable       (const string&);
    CBigNum         calculate               (const string&);
    void            display                 (const string&) const;
    void            saveHistory             (const string&, const string&);
    EValType        determineType           (const string&) const;
    bool            isOperator              (const string&) const;
    void            pushToStack             (const string &, stack<CExpression*> &) const;
    CExpression *   performOperation        (CExpression*, CExpression*, const string&);

public:
    CCalculator() { cout << "Welcome to super high precision calculator!" << endl
                         << "-To creat a variable type: <variable name> = <value>" << endl
                         << " *Variable names can only consist of letters and numbers having letter as the very first symbol" << endl
                         << "-To quit type \"quit\"" << endl;}
    void    run();
};