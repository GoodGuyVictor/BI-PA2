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
using namespace std;

class InvalidInput{};

enum EValType { VAL_INT, VAL_LONGINT, VAL_DEC };

class COperand
{
protected:
    string m_value;
    EValType m_type;

public:
    COperand                                    () = default;
    COperand                                    (const string & val, EValType type)
            : m_value(val), m_type(type) {};
    virtual ~COperand                           () = default;

            COperand & operator+                (const COperand & other);

//    virtual COperand * addInteger               (const COperand & other) = 0;
//    virtual COperand * addLongInteger           (const COperand & other) = 0;
//    virtual COperand * addDecimal               (const COperand & other) = 0;
//
//    virtual COperand * subtractInteger          (const COperand & other) = 0;
//    virtual COperand * subtractLongInteger      (const COperand & other) = 0;
//    virtual COperand * subtractDecimal          (const COperand & other) = 0;
//
//    virtual COperand * multiplyByInteger        (const COperand & other) = 0;
//    virtual COperand * multiplyByLongInteger    (const COperand & other) = 0;
//    virtual COperand * multiplyByDecimal        (const COperand & other) = 0;
//
//    virtual COperand * devideByInteger          (const COperand & other) = 0;
//    virtual COperand * devideByLongInteger      (const COperand & other) = 0;
//    virtual COperand * devideByDecimal          (const COperand & other) = 0;
};



class CInteger : public COperand
{
public:
    CInteger() = default;
    explicit CInteger(const string & val) : COperand(val, VAL_INT) {}
};



class CLongInteger : public CInteger
{
public:
    CLongInteger(const string & val) : COperand(val, VAL_LONGINT) {};
};



class CDecimal : public COperand
{
public:
    explicit CDecimal(const string & val) : COperand(val, VAL_DEC) {}

};



class CVariable : public COperand
{
private:
    string m_name;
public:
    explicit CVariable(const string & name, const string & val, EValType type)
            : COperand(val, type), m_name(name) {}
};



class CParser
{
private:
    vector<string> m_output;
    unordered_map<char, int> m_opPrecedence = {
            {'+', 10},
            {'-', 10},
            {'*', 20},
            {'/', 20},
            {'%', 20},
            {'(', 30},
    };

    void shuntingYard                   (const string &);
    bool isOperator                     (const char) const;
    void popOperatorFromStackToOutput   (stack<char> &);
public:
    CParser() = default;
    ~CParser() = default;
    vector<string> parse(const string &);
};


void CParser::shuntingYard(const string &input)
{
    string tmp_operand;
    stack<char> operatorStack;

    for (auto it = input.begin(); it < input.end(); it++)
    {
        if(isdigit(*it))
            tmp_operand += *it;
        else if(isOperator(*it))
        {
            if(*it == '-' && it == input.begin())
                tmp_operand += *it;
            else if(*it == '-' && *(it-1) == '(')
                tmp_operand += *it;
            else
            {
                if(!tmp_operand.empty()) {
                    m_output.push_back(tmp_operand);
                    tmp_operand = "";
                }

                if(*it == ')')
                {
                    do
                    {
                        popOperatorFromStackToOutput(operatorStack);
                    } while(operatorStack.top() != '(');
                    operatorStack.pop();
                }
                else
                {
                    if(!operatorStack.empty())
                    {
                        while(m_opPrecedence[operatorStack.top()] >= m_opPrecedence[*it]
                              && operatorStack.top() != '(')
                        {
                            popOperatorFromStackToOutput(operatorStack);
                            if(operatorStack.empty())
                                break;
                        }
                    }

                    operatorStack.push(*it);
                }
            }
        }
        else if(isalpha(*it))
        {
            tmp_operand += *it;
        }
        else
            throw InvalidInput();
    }

    if(!tmp_operand.empty()) {
        m_output.push_back(tmp_operand);
        tmp_operand = "";
    }

    while(!operatorStack.empty())
        popOperatorFromStackToOutput(operatorStack);
}

vector<string> CParser::parse(const string & input)
{
    shuntingYard(input);
    return m_output;
}

bool CParser::isOperator(const char op) const
{
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '(' || op == ')';
}

void CParser::popOperatorFromStackToOutput(stack<char> &operatorStack)
{
    string tmp_operator;
    tmp_operator = operatorStack.top();
    operatorStack.pop();
    m_output.push_back(tmp_operator);
}



class CCalculator
{
private:
    vector<CVariable> m_variables;
    vector<string> m_history;

    void removeWhiteSpaces(string &);
    void createNewVariable(const string&);
    string calculate(const string&);
    void display(const string&) const;
    void saveHistory(const string&, const string&);
    EValType determineType(const string&) const;
    bool isOperator(const string&) const;

public:
    CCalculator() { cout << "Welcome to super high precision calculator!" << endl
                         << "-To creat a variable type: <variable name> = <value>" << endl
                         << " *Variable names can consist of letters and number having letter as the very first symbol" << endl
                         << "-To quit type \"quit\"" << endl;}
    void run();
    string readInput();
};

void CCalculator::run()
{
    string input;
    string result;

    while(true)
    {
        input = readInput();
        if(input == "variable")
            continue;
        if(input == "quit")
            break;
        result = calculate(input);
        display(result);
        saveHistory(input, result);
    }
}

string CCalculator::readInput()
{
    string input;

    cout << ">";
    getline(cin, input, '\n');
    removeWhiteSpaces(input);

    //adding new variable
    if(input.find('=') != string::npos)
    {
        m_history.push_back(input);
        createNewVariable(input);
        return "variable";
    }

    return input;
}

void CCalculator::removeWhiteSpaces(string &str)
{
    for (auto it = str.begin(); it < str.end(); it++)
        while (*it == ' ')
            str.erase(it);
}

void CCalculator::createNewVariable(const string &input)
{
    char * token;
    token = strtok((char*)input.c_str(), "=");
    string name(token);
    token = strtok(NULL, "=");
    string val(token);
    m_variables.emplace_back(CVariable(name, val, determineType(val)));
}

string CCalculator::calculate(const string & input)
{
    CParser parser;
    vector<string> parsedOutput;
    stack<COperand*> operandStack;

    if(!input.empty())
    {
        parsedOutput.clear();
        parsedOutput = parser.parse(input) ;
        int x = 0;

        for(const auto & output : parsedOutput)
        {
            if(isOpeoutput)

            switch (determineType(output))
            {
                case VAL_INT: { COperand *p = new CInteger(output); break; }
                case VAL_LONGINT: { COperand *p = new CLongInteger(output); break; }
                case VAL_DEC: { COperand *p = new CDecimal(output); break; }
            }
        }
    }
}

void CCalculator::display(const string & result) const
{
    cout << "----------" << endl;
    cout << result << endl;
}

void CCalculator::saveHistory(const string & input, const string & result)
{
    string tmp;
    tmp += input;
    tmp += "=";
    tmp += result;
    m_history.push_back(tmp);
}

EValType CCalculator::determineType(const string & number) const
{
    if(number.find('.') != string::npos || number.find('e') != string::npos)
        return VAL_DEC;

    if(number.size() > 6)
        return VAL_LONGINT;

    return VAL_INT;
}

bool CCalculator::isOperator(const string & op) const
{
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
}


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

void extractInt(const string & str)
{
    stringstream ss;
    vector<int> tmpCoords;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found) {
            tmpCoords.push_back(found);
        }
    }
    cout << "extracted ints:" << endl;
    for (auto &it : tmpCoords)
        cout << it << " ";
}

//todo list
//input validation
//((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1))