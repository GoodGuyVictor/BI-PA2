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
            result = calculate(input);
            result.print();
            saveHistory(input, result);
        } catch (std::exception & e) {
            std::cout << "Input error: " << e.what() << std::endl;
        }
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

    if(!isalpha(name[0]))
        throw InvalidVariableName();

    if(containIllegalChar(name))
        throw InvalidVariableName();

    token = strtok(NULL, "=");
    string val(token);
    CBigNum result = calculate(val);
    val = result.toString();

    m_variables.emplace_back(CVariable(name, val));
}

CBigNum CCalculator::calculate(const string & input)
{
    CParser parser;
    vector<string> parsedInput;
    stack<CExpression*> exprStack;

    if(!input.empty())
    {
//        parsedInput.clear();
        parsedInput = parser.parse(input) ;

        for(const auto & token : parsedInput)
        {
            if(!isOperator(token))
                pushToStack(token, exprStack);
            else
            {
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
    tmp += " = ";
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
    myfile.open("calculator.txt");

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
