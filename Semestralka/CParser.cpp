#include "CParser.h"
#include "Exceptions.h"

void CParser::shuntingYard(const string &input)
{
    string tmp_operand;
    stack<char> operatorStack;

    for (auto it = input.begin(); it < input.end(); it++) {
        if(isdigit(*it))
            tmp_operand += *it;
        else if(isalpha(*it)) {
            if(!tmp_operand.empty() && isdigit(tmp_operand[0]))
                throw InvalidValue();
            else
                tmp_operand += *it;
        }
        else if(*it == '.')
            tmp_operand += *it;
        else if(isOperator(*it)) {
            if(*it == '-' && it == input.begin())
                tmp_operand += *it;
            else if(*it == '-' && *(it-1) == '(')
                tmp_operand += *it;
            else {
                if(!tmp_operand.empty()) {
                    m_output.push_back(tmp_operand);
                    tmp_operand = "";
                }

                if(*it == ')') {
                    while(operatorStack.top() != '(') {
                        popOperatorFromStackToOutput(operatorStack);
                        if(operatorStack.empty())
                            throw MissingParanthesis();
                    }
                    operatorStack.pop();
                } else {
                    if(!operatorStack.empty()) {
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
        else
            throw InvalidInput();
    }

    if(!tmp_operand.empty()) {
        m_output.push_back(tmp_operand);
        tmp_operand = "";
    }

    while(!operatorStack.empty()) {
        if(operatorStack.top() == '(')
            throw MissingParanthesis();
        popOperatorFromStackToOutput(operatorStack);
    }
}

vector<string> CParser::parse(const string & input)
{
    shuntingYard(input);
    return m_output;
}

bool CParser::isOperator(const char token) const
{
    return token == '+' || token == '-' || token == '*' || token == '/' || token == '%' || token == '(' || token == ')';
}

void CParser::popOperatorFromStackToOutput(stack<char> &operatorStack)
{
    string tmp_operator;
    tmp_operator = operatorStack.top();
    operatorStack.pop();
    m_output.push_back(tmp_operator);
}