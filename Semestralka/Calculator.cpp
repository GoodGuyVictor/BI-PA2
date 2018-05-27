#include <cstring>
#include "Calculator.h"
#include "Parser.h"
#include "Integer.h"
#include "LongInteger.h"
#include "Decimal.h"
#include "AddExp.h"
#include "SubtractExp.h"
#include "MultiplyExp.h"
#include "DevideExpr.h"
#include "Mod.h"
#include "Exceptions.h"
#include <regex>

void Calculator::run()
{
    string input;
    CBigNum result;

    while(true)
    {
        input = readInput();
        if(input == "variable")
            continue;
        if(input == "quit")
            break;
        result = calculate(input);
        result.print();
//        saveHistory(input, result);
    }
}

string Calculator::readInput()
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

void Calculator::removeWhiteSpaces(string &str)
{
    for (auto it = str.begin(); it < str.end(); it++)
        while (*it == ' ')
            str.erase(it);
}

void Calculator::createNewVariable(const string &input)
{
    char * token;
    token = strtok((char*)input.c_str(), "=");
    string name(token);
    token = strtok(NULL, "=");
    string val(token);
    m_variables.emplace_back(CVariable(name, val));
}

CBigNum Calculator::calculate(const string & input)
{
    CParser parser;
    vector<string> parsedInput;
    stack<Expression*> exprStack;

    if(!input.empty())
    {
        parsedInput.clear();
        parsedInput = parser.parse(input) ;

        for(const auto & token : parsedInput)
        {
            if(!isOperator(token))
                pushToStack(token, exprStack);
            else
            {
                Expression *rVal = exprStack.top(); exprStack.pop();
                Expression *lVal = exprStack.top(); exprStack.pop();

                Expression *result = performOperation(lVal, rVal, token);
                exprStack.push(result);
            }
        }

        CBigNum finalResult = exprStack.top()->evaluate();
        delete exprStack.top();
        exprStack.pop();
        return finalResult;
    }
}

void Calculator::saveHistory(const string & input, const string & result)
{
    string tmp;

    tmp += input;
    tmp += " = ";
    tmp += result;
    m_history.push_back(tmp);
}

EValType Calculator::determineType(const string & number) const
{
    if(number.find('.') != string::npos)
        return VAL_DEC;

    if(number.size() > 6)
        return VAL_LONGINT;

    if(isalpha(number[0]))
        return VAL_VAR;

    return VAL_INT;
}

bool Calculator::isOperator(const string & op) const
{
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
}

void Calculator::pushToStack(const string & operand, stack<Expression*> &stack) const
{
    switch (determineType(operand))
    {
        case VAL_INT: {
            Expression *p = new CInteger(operand);
            stack.push(p);
            break;
        }
        case VAL_LONGINT: {
            Expression *p = new CLongInteger(operand);
            stack.push(p);
            break;
        }
        case VAL_DEC: {
            Expression *p = new Decimal(operand);
            stack.push(p);
            break;
        }
        case VAL_VAR: {
            Expression *p = NULL;
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

Expression *Calculator::performOperation(Expression * lVal, Expression * rVal, const string & op)
{
    if(op == "+")
        return new CAddExp(lVal, rVal);

    if(op == "-")
        return new SubtractExp(lVal, rVal);

    if(op == "*")
        return new CMultiplyExp(lVal, rVal);

    if(op == "/")
        return new CDevideExp(lVal, rVal);

    if(op == "%")
        return new CMod(lVal, rVal);
}