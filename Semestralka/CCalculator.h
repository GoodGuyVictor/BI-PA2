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
    CBigNum         calculate               (const string&);
    void            saveHistory             (const string&, const CBigNum&);
    EValType        determineType           (const string&) const;
    bool            isOperator              (const string&) const;
    void            pushToStack             (const string &, stack<CExpression*> &) const;
    CExpression *   performOperation        (CExpression*, CExpression*, const string&);
    bool            containIllegalChar      (const string &) const;
    void            addVariable             (std::string);
    void            validateVariableName    (const std::string &) const;

public:
    CCalculator() { cout << "Welcome to arbitrary precision calculator!" << endl
                         << "-To creat a variable type: <variable name> = <value>" << endl
                         << " *Variable names can only consist of letters and numbers having letter as the very first symbol" << endl
                         << "-To quit type \"quit\"" << endl;}
    void    run();
    void    saveToFile() const;
    void            readFromFile            (std::string = "data.txt");

};