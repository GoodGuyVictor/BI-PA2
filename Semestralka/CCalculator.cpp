#include <cstring>
#include "CCalculator.h"
#include "CParser.h"
#include "CInteger.h"
#include "CLongInteger.h"
#include "CDecimal.h"
#include "CAddExp.h"
#include "CSubtractExp.h"
#include "CMultiplyExp.h"
#include "CDevideExpr.h"
#include "CMod.h"
#include "Exceptions.h"
#include <regex>
#include <fstream>

void CCalculator::run()
{
    string input;
    CBigNum result;

    while(true)
    {
        try {
            input = readInput();
            if(input == "variable")
                continue;
            if(input == "quit")
                break;
            if(input == "save") {
                saveToFile();
                continue;
            }
            if(input == "read") {
                readFromFile();
                continue;
            }
            if(input.empty())
                continue;
            result = calculate(input);
            result.print();
            saveHistory(input, result);
        } catch (std::exception & e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }
    }
}

string CCalculator::readInput()
{
    string input;

    cout << ">";
    getline(cin, input, '\n');
    removeWhiteSpaces(input);

    if(input.find('=') != string::npos)
    {
        addVariable(input);
        m_history.push_back(input);
        return "variable";
    }

    if(input == "save")
        return "save";

    if(input == "read")
        return "read";

    return input;
}

void CCalculator::removeWhiteSpaces(string &str)
{
    for (auto it = str.begin(); it < str.end(); it++)
        while (*it == ' ')
            str.erase(it);
}

CBigNum CCalculator::calculate(const string & input)
{
    CParser parser;
    vector<string> parsedInput;
    stack<CExpression*> exprStack;

    if(!input.empty())
    {
        parsedInput = parser.parse(input) ;

        for(const auto & token : parsedInput) {
            if(!isOperator(token))
                pushToStack(token, exprStack);
            else {
                CExpression *rVal = exprStack.top(); exprStack.pop();
                CExpression *lVal = exprStack.top(); exprStack.pop();

                CExpression *result = performOperation(lVal, rVal, token);
                exprStack.push(result);
            }
        }

        CBigNum finalResult = exprStack.top()->evaluate();
        delete exprStack.top();
        exprStack.pop();
        return finalResult;
    }
}

void CCalculator::saveHistory(const string & input, const CBigNum & result)
{
    string tmp;

    tmp += input;
    tmp += "=";
    tmp += result.toString();
    m_history.push_back(tmp);
}

EValType CCalculator::determineType(const string & number) const
{
    if(number.find('.') != string::npos)
        return VAL_DEC;

    if(number.size() > 6)
        return VAL_LONGINT;

    if(isalpha(number[0]))
        return VAL_VAR;

    return VAL_INT;
}

bool CCalculator::isOperator(const string & op) const
{
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
}

void CCalculator::pushToStack(const string & operand, stack<CExpression*> &stack) const
{
    switch (determineType(operand))
    {
        case VAL_INT: {
            CExpression *p = new CInteger(operand);
            stack.push(p);
            break;
        }
        case VAL_LONGINT: {
            CExpression *p = new CLongInteger(operand);
            stack.push(p);
            break;
        }
        case VAL_DEC: {
            CExpression *p = new Decimal(operand);
            stack.push(p);
            break;
        }
        case VAL_VAR: {
            CExpression *p = NULL;
            for(const auto & it : m_variables)
                if(it.getName() == operand)
                    p = it.clone();

            if(p == NULL)
                throw InvalidVariableName();
            else
                stack.push(p);

            break;
        }
    }
}

CExpression *CCalculator::performOperation(CExpression * lVal, CExpression * rVal, const string & op)
{
    if(op == "+")
        return new CAddExp(lVal, rVal);

    if(op == "-")
        return new CSubtractExp(lVal, rVal);

    if(op == "*")
        return new CMultiplyExp(lVal, rVal);

    if(op == "/")
        return new CDevideExp(lVal, rVal);

    if(op == "%")
        return new CMod(lVal, rVal);
}

void CCalculator::saveToFile() const
{
    ofstream myfile;
//    myfile.open("/home/victor/gitHubRepos/PA2/Semestralka/output/calculator.txt");
    myfile.open("data.txt");

    if(myfile.is_open()) {
        myfile << "VARIABLES" << std::endl;
        for(const auto & it : m_variables)
                myfile << it.toString() << std::endl;

        myfile << "HISTORY" << std::endl;
        for(const auto & it : m_history)
            myfile << it << std::endl;
    }

    myfile.close();
}

bool CCalculator::containIllegalChar(const string & varName) const
{
    vector<char> illegals = {'!', '@', '#', '$', '%', '^', ':', ';', '*', '(', ')', '-',
                             '_', '"', '\\', '\'', ',', '.', '/', '+', '?', '>', '<', '`', '~'};

    for(const auto & it : varName)
        for(const auto & illegal : illegals)
            if(it == illegal)
                return true;

    return false;
}

void CCalculator::addVariable(std::string input)
{
    char * token;
    token = strtok((char*)input.c_str(), "=");
    string name(token);
    validateVariableName(name);

    token = strtok(NULL, "=");
    string val(token);
    CBigNum value = calculate(val);

    //if variable exists reset its value
    for(auto & it : m_variables)
        if(it.getName() == name) {
            it.setValue(value);
            return;
        }
    //else creating new one
    m_variables.emplace_back(CVariable(name, value));
}

void CCalculator::validateVariableName(const std::string & name) const
{
    if(!isalpha(name[0]))
        throw InvalidVariableName();

    if(containIllegalChar(name))
        throw InvalidVariableName();
}

void CCalculator::readFromFile(std::string filename)
{
    ifstream myfile;
    myfile.open(filename);

    if(myfile.is_open()) {
        std::string input;
        myfile >> input;
        if(input == "VARIABLES") {
            myfile >> input;//discard VARIABLES label
            while(input != "HISTORY") {
                addVariable(input);
                myfile >> input;
            }

            myfile >> input;//discard HISTORY label
            while(!myfile.eof()) {
                m_history.push_back(input);
                myfile >> input;
            }
        } else {
            myfile.close();
            throw InvalidFileFormat();
        }
    } else {
        myfile.close();
        throw InvalidFileName();
    }

    myfile.close();
}
