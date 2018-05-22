//
// Created by victor on 22.5.18.
//

#include <algorithm>
#include <stack>
#include <iostream>
#include <iomanip>
#include "CLongInteger.h"
#include "CAddExp.h"
#include "CInteger.h"

void CBigNum::print() const
{
    std::cout << "----------" << std::endl;

    if(m_sgn)
        std::cout << "-";

    for(auto it = m_exponent.rbegin(); it < m_exponent.rend(); it++)
        if(*it) //do not print leading zeros
            std::cout << *it;

    if(m_fraction)
        std::cout << "." << m_fraction;

    std::cout << std::endl;
}

CBigNum & CBigNum::operator+(const CBigNum &other)
{
    if(m_sgn == true && other.m_sgn == false) {
        m_sgn = false;
        CBigNum copy = other;
        return copy.operator-(*this);
    } else if(m_sgn == false && other.m_sgn == true) {
        CBigNum copy = other;
        return operator-(copy.operator-());
    }

    std::vector<uint32_t> exponent1 = m_exponent;
    std::vector<uint32_t> exponent2 = other.m_exponent;

    uint32_t fractoin1 = m_fraction;
    uint32_t fractoin2 = other.m_fraction;

    expandFewerNumberWithZeros(exponent1, exponent2);

    std::vector<uint32_t> result;
    uint32_t tmp;
    unsigned short carry = 0;

    m_fraction = addFractions(fractoin1, fractoin2, carry);

    for(size_t i = 0; i < exponent1.size(); i++) {
        tmp = exponent1[i] + exponent2[i] + carry;
        carry = getCarry(tmp);
        tmp %= 1000000000;
        result.push_back(tmp);
    }

    if(carry)
        result.push_back(carry);

    m_exponent = result;
    return *this;
}

CBigNum &CBigNum::operator-(const CBigNum &other)
{
    if(m_sgn == false && other.m_sgn == true) {
        CBigNum copy = other;
        return operator+(copy.operator-());
    }
    else if (m_sgn == true && other.m_sgn == false) {
        m_sgn = false;
        CBigNum res = operator+(other);
        return res.operator-();
    }

    std::vector<uint32_t> exponent1 = m_exponent;
    std::vector<uint32_t> exponent2 = other.m_exponent;

    uint32_t fractoin1 = m_fraction;
    uint32_t fractoin2 = other.m_fraction;

    expandFewerNumberWithZeros(exponent1, exponent2);

    unsigned short carry = 0;
    m_fraction = subtractFractions(fractoin1, fractoin2, carry);

    std::vector<uint32_t> result;
    long int tmp;
    for(size_t i = exponent1.size() - 1; i >= 0; i--) {
        if(exponent1[i] > exponent2[i]) {
            for(size_t j = 0; j < exponent1.size(); j++) {
                tmp = (long)exponent1[j] - (long)exponent2[j] - carry;
                if(tmp < 0) {
                    carry = 1;
                    tmp = UINT32_MAX + tmp; //modulo
                } else
                    carry = 0;
                result.push_back((uint32_t)tmp);
            }
            m_exponent = result;
            m_sgn = false;
            return *this;
        } else if(exponent1[i] < exponent2[i]) {
            for(size_t j = 0; j < exponent1.size(); j++) {
                tmp = (long)exponent1[j] - (long)exponent2[j] + carry;
                if(tmp < 0) {
                    tmp *= -1;
                    carry = 0;
                }
                else {
                    carry = 1;
                    tmp = UINT32_MAX - tmp;
                }
                result.push_back((uint32_t)tmp);
            }
            m_exponent = result;
            m_sgn = true;
            return *this;
        }
    }
    result.push_back(0);
    m_exponent = result;
    m_sgn = false;
    return *this;
}

CBigNum &CBigNum::operator-()
{
    m_sgn = !m_sgn;
    return *this;
}

CBigNum CBigNum::operator* (const CBigNum & other)
{
    std::vector<uint32_t> exponent1 = m_exponent;
    std::vector<uint32_t> exponent2 = other.m_exponent;

    uint32_t fractoin1 = m_fraction;
    uint32_t fractoin2 = other.m_fraction;

    expandFewerNumberWithZeros(exponent1, exponent2);

    size_t len = exponent1.size();
    uint32_t carry = 0;
    unsigned long long tmpProduct;
    std::string tmpString;
    std::string resultString;
    std::stringstream buffer;
    std::stringstream ss;
    std::vector<std::string> results;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            tmpProduct = (unsigned long long)exponent2[i] * (unsigned long long)exponent1[j] + carry;
            buffer << std::setw(9) << std::setfill('0') << (uint32_t)(tmpProduct % 1000000000);
            buffer >> tmpString;
            std::reverse(tmpString.begin(), tmpString.end());
            buffer.clear();
            ss << tmpString;
            carry = tmpProduct / 1000000000;
        }
        if(carry) {
            buffer << carry;
            buffer >> tmpString;
            std::reverse(tmpString.begin(), tmpString.end());
            ss << tmpString;
            buffer.clear();
            carry = 0;
        }
        ss >> resultString;
        std::reverse(resultString.begin(), resultString.end());
        for(int k = 0; k < 9 * i; k++)
            resultString.push_back('0');
        while(resultString.front() == '0')
            resultString.erase(0,1);
        results.push_back(resultString);
        tmpString.clear();
        ss.clear();
    }

    std::stack<CExpression*> exprStack;

    CExpression * p;
    for(const auto & it : results) {
        if(it.size() > 6)
            p = new CLongInteger(it);
        else
            p = new CInteger(it);
        exprStack.push(p);
    }

    if(exprStack.size() == 1) {
        CBigNum finalResult = exprStack.top()->evaluate();
        if(m_sgn && !other.m_sgn || !m_sgn && other.m_sgn)
            finalResult.operator-();
        return finalResult;
    }

    CExpression * rVal;
    CExpression * lVal;
    do {
        rVal = exprStack.top(); exprStack.pop();
        lVal = exprStack.top(); exprStack.pop();

        p = new CAddExp(lVal, rVal);
        exprStack.push(p);

    } while(exprStack.size() != 1);

    CBigNum finalResult = exprStack.top()->evaluate();
    if(m_sgn && !other.m_sgn || !m_sgn && other.m_sgn)
        finalResult.operator-();
    return finalResult;
}
