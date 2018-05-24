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
#include "CSubtractExp.h"

void CBigNum::print() const
{
    std::cout << "----------" << std::endl;

    if(m_sgn)
        std::cout << "-";

    std::string output = toString(m_exponent);
    while(output[0] == '0')
        output.erase(0,1);
    std::cout << output;

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
                    tmp = 1000000000 + tmp; //modulo
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
                    tmp = 1000000000 - tmp;
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

    int tens = 0;
    tens = eliminateEndingZeros(exponent1, exponent2);

    expandFewerNumberWithZeros(exponent1, exponent2);

    CBigNum product = multiplicationAlgorithm(exponent1, exponent2);

    while(tens) {
        product.multiplyByTen();
        tens--;
    }

    if(m_sgn && !other.m_sgn || !m_sgn && other.m_sgn)
        product.operator-();

    return product;
}

uint32_t CBigNum::addFractions(uint32_t f1, uint32_t f2, unsigned short &carry) const
{
    int i = 10;
    int cnt1 = 0, cnt2 = 0;

    while(f1 / i) {
        cnt1++;
        i *= 10;
    }

    i = 10;
    while(f2 / i) {
        cnt2++;
        i *= 10;
    }

    uint32_t result;
    if(cnt1 == cnt2) {
        uint64_t tmp = (uint64_t)f1 + (uint64_t)f2;
        result = (uint32_t)tmp;
        carry = tmp >> 32;
    } else if(cnt1 > cnt2) {
        for(int j = 0; j < abs(cnt1 - cnt2); j++)
            f2 *= 10;
        uint64_t tmp = (uint64_t)f1 + (uint64_t)f2;
        result = (uint32_t)tmp;
        carry = tmp >> 32;
    } else {
        for(int j = 0; j < abs(cnt1 - cnt2); j++)
            f1 *= 10;
        uint64_t tmp = (uint64_t)f1 + (uint64_t)f2;
        result = (uint32_t)tmp;
        carry = tmp >> 32;
        cnt1 = cnt2;
    }

    int cnt3 = 0;
    i = 10;
    while(result / i) {
        cnt3++;
        i *= 10;
    }

    if(cnt3 > cnt1) {
        carry = 1;
        result %= i / 10;
    }

    return result;
}

uint32_t CBigNum::subtractFractions(uint32_t f1, uint32_t f2, unsigned short &carry)
{
    long tmp = (long)f1 - (long)f2;
    if(tmp < 0) {
        carry = 1;
        tmp = 1000000 + tmp;
    }
    return (uint32_t)tmp;
}

unsigned short CBigNum::getCarry(const uint32_t sum) const
{
    if(sum / 1000000000)
        return 1;
    else
        return 0;
}

void CBigNum::expandFewerNumberWithZeros(std::vector<uint32_t> &exponent1, std::vector<uint32_t> &exponent2)
{
    //if lengths are different expand the shorter one with zeros
    size_t n;
    if(exponent1.size() == exponent2.size())
        n = exponent1.size();
    else if(exponent1.size() > exponent2.size()) {
        n = exponent2.size();
        for(size_t i = n; i < exponent1.size(); i++)
            exponent2.push_back(0);
    }
    else {
        n = exponent1.size();
        for(size_t i = n; i < exponent2.size(); i++)
            exponent1.push_back(0);
    }
}

CBigNum::CBigNum(bool sgn, const std::vector<uint32_t> &val)
{
    m_sgn = sgn;
    m_exponent = val;
    m_fraction = 0;
}

CBigNum::CBigNum(double val)
{
    if(val < 0) {
        m_sgn = true;
        val *= -1;
    } else
        m_sgn = false;

    std::string dStr = std::to_string(val);

    char * token;
    token = strtok((char*)dStr.c_str(), ".");
    std::stringstream ss;
    ss << token;
    uint32_t exponent;
    ss >> exponent;
    m_exponent.push_back(exponent);
    ss.clear();

    token = strtok(NULL, ".");
    ss << token;
    uint32_t fraction;
    ss >> fraction;
    m_fraction = fraction;
}

CBigNum::CBigNum(int val)
{
    if(val < 0) {
        m_sgn = true;
        val *= -1;
    } else
        m_sgn = false;
    m_exponent.push_back((uint32_t)val);
    m_fraction = 0;
}

CBigNum CBigNum::operator/(const CBigNum &other)
{
    std::vector<uint32_t> exponent1 = m_exponent;
    std::vector<uint32_t> exponent2 = other.m_exponent;

    if(exponent1.size() == 1 && exponent2.size() == 1)
        return CBigNum((int)(exponent1[0] / exponent2[0]));


    //if dividend is equal to divisor that result is 1
    if(exponent1 == exponent2)
        return CBigNum(1);


    if(exponent1.size() == exponent2.size()) {
        int len = (int)exponent1.size();

        for(int i = len - 1; i >= 0; i--)
            //if dividend is less than divisor than quotient is 0
            if(exponent1[i] < exponent2[i])
                return CBigNum(); //default constructor result is 0
            else if(exponent1[i] > exponent2[i])
                break;
    } else if(exponent1.size() < exponent2.size())
        return CBigNum(); //default constructor result is 0

//    if(exponent1.size() != exponent2.size())
//        expandFewerNumberWithZeros(exponent1, exponent2);

    std::string quotient;
    std::string remainder;

    divideAlgorithm(exponent1, exponent2, quotient, remainder);

    return CLongInteger(quotient).evaluate();
}

std::string CBigNum::toString(const std::vector<uint32_t> &value) const
{
    std::stringstream ss;
    for(auto it = value.rbegin(); it < value.rend(); it++)
        ss << std::setw(9) << std::setfill('0') << *it;
    std::string result;
    ss >> result;
    return result;
}

bool CBigNum::operator>=(const CBigNum & other)
{

    std::string value1 = toString(m_exponent);
    std::string value2 = toString(other.m_exponent);

    while(value1[0] == '0')
        value1.erase(0,1);

    while(value2[0] == '0')
        value2.erase(0,1);

    size_t len1 = value1.size();
    size_t len2 = value2.size();

    if(len1 > len2)
        return true;
    else if(len1 < len2)
        return false;
    else {
        size_t len = len1; //len1 == len2
        for(size_t i = 0; i < len; i++)
            if(value1[i] - '0' > value2[i] - '0')
                return true;
            else if(value1[i] - '0' < value2[i] - '0')
                return false;

        return true;
    }
}

void CBigNum::divideAlgorithm(const std::vector<uint32_t> & val1,
                              const std::vector<uint32_t> & val2,
                              std::string & quotient, std::string & remainder) const
{
    std::string stringDividend = toString(val1);
    std::string stringDivisor = toString(val2);
//    std::string quotient;
//    std::string remainder;
    std::stringstream ss;

    while(stringDividend[0] == '0')
        stringDividend.erase(0,1);

    while(stringDivisor[0] == '0')
        stringDivisor.erase(0,1);

    size_t len2 = stringDivisor.size();

    std::string dividendChunkString = stringDividend.substr(0, len2);
    for(size_t i = 0; i < dividendChunkString.size(); i++)
        if(dividendChunkString[i] - '0' < stringDivisor[i] - '0') {
            dividendChunkString = stringDividend.substr(0, len2 + 1);
            stringDividend.erase(0, len2 + 1);
            break;
        } else if(dividendChunkString[i] - '0' > stringDivisor[i] - '0') {
            stringDividend.erase(0, len2);
            break;
        }

    CBigNum dividendChunk = CLongInteger(dividendChunkString).evaluate();
    CBigNum divisor = CLongInteger(stringDivisor).evaluate();

    size_t wholePart;

    while(true) {
        wholePart = 0;
        while(dividendChunk >= divisor) {
            wholePart++;
            dividendChunk = dividendChunk - divisor;
        }
        ss << wholePart;
        std::string tmpQuotient;
        ss >> tmpQuotient;
        quotient += tmpQuotient;
        ss.clear();

        if(!stringDividend.empty()) {
            dividendChunk.multiplyByTen();
            dividendChunk = dividendChunk + CBigNum(stringDividend[0] - '0');
            stringDividend.erase(0,1);
        } else
            break;
    }
    remainder = toString(dividendChunk);
    if(remainder.empty())
        remainder = "0";
}

std::string CBigNum::toString(const CBigNum & number) const
{
    std::string result;
    if(m_sgn)
        result += "-";
    result += toString(m_exponent);
    return result;
}

void CBigNum::multiplyByTen()
{
    long tmp;
    uint32_t carry = 0;

    for(size_t i = 0; i < m_exponent.size(); i++) {
        tmp = (long)m_exponent[i] * 10 + carry;
        carry =  tmp / 1000000000; //10 ^ 9
        m_exponent[i] = (uint32_t)(tmp % 1000000000); //10 ^ 9
    }

    if(carry)
        m_exponent.push_back(carry);
}

int CBigNum::eliminateEndingZeros(std::vector<uint32_t> & exponent1, std::vector<uint32_t> & exponent2) const
{
    int zerosCnt = 0;
    std::string exponent1String = toString(exponent1);
    std::string exponent2String = toString(exponent2);

    for(size_t i = exponent1String.size() - 1; i >= 0; i--)
        if(exponent1String[i] == '0') {
            zerosCnt++;
            exponent1String.erase(i, 1);
        } else
            break;

    for(size_t i = exponent2String.size() - 1; i >= 0; i--)
        if(exponent2String[i] == '0') {
            zerosCnt++;
            exponent2String.erase(i, 1);
        } else
            break;

    exponent1 = toBigInt(exponent1String);
    exponent2 = toBigInt(exponent2String);

    return zerosCnt;
}

std::vector<uint32_t> CBigNum::toBigInt(std::string &text) const
{
    std::vector<uint32_t> result;
    int len = text.size();
    int portions = len / 9;
    std::stringstream ss;
    uint32_t tmp;

    for(int i = 0; i < portions; i++) {
        ss << text.substr(text.size() - 9, 9);
        ss >> tmp;
        result.push_back(tmp);
        text.erase(text.size() - 9, 9);
        ss.clear();
    }

    if(!text.empty()) {
        ss << text;
        ss >> tmp;
        result.push_back(tmp);
    }

    return result;
}

CBigNum CBigNum::multiplicationAlgorithm(const std::vector<uint32_t> & factor1,
                                         const std::vector<uint32_t> & factor2) const
{
    size_t len = factor1.size();//factor1.size() == factor2.size()
    uint32_t carry = 0;
//    std::string resultString;
//    std::stringstream buffer;
//    std::stringstream ss;
    std::vector<std::string> intermediateResults;
    std::vector<std::string> intermediateProduct;

    for (size_t i = 0; i < len; i++) {
//        std::string tmpString;
        if(factor2[i] == 0)
            continue;
        for (size_t j = 0; j < len; j++) {
            unsigned long long tmpProduct = (unsigned long long)factor2[i] * (unsigned long long)factor1[j] + carry;
            intermediateProduct.push_back( toString( (uint32_t)(tmpProduct % 1000000000) ) ); //10 ^ 9
            carry = tmpProduct / 1000000000;
//            buffer << std::setw(9) << std::setfill('0') << (uint32_t)(tmpProduct % 1000000000);//10 ^ 9
//            buffer >> tmpString;
//            std::reverse(tmpString.begin(), tmpString.end());
//            ss << tmpString;
//            buffer.clear();
        }
        if(carry) {
//            buffer << carry;
//            buffer >> tmpString;
//            std::reverse(tmpString.begin(), tmpString.end());
//            ss << tmpString;
//            buffer.clear();
            intermediateProduct.push_back( toString(carry) );
            carry = 0;
        }
//        ss >> resultString;
//        std::reverse(resultString.begin(), resultString.end());
        std::string intermediateProductString;
        for(auto it = intermediateProduct.rbegin(); it < intermediateProduct.rend(); it++) {
            intermediateProductString += *it;
        }
        for(int k = 0; k < 9 * i; k++)
            intermediateProductString.push_back('0');
        while(intermediateProductString.front() == '0')
            intermediateProductString.erase(0,1);
        intermediateResults.push_back(intermediateProductString);
        intermediateProduct.clear();
//        tmpString.clear();
//        ss.clear();
    }

    std::stack<CExpression*> exprStack;

    for(const auto & summand : intermediateResults) {
        CExpression * p;
        if(summand.size() > 6)
            p = new CLongInteger(summand);
        else
            p = new CInteger(summand);
        exprStack.push(p);
    }

//    if(exprStack.size() == 1) {
//        CBigNum product = exprStack.top()->evaluate();
//        if(m_sgn && !other.m_sgn || !m_sgn && other.m_sgn)
//            product.operator-();
//        return product;
//    } else {
//        CExpression * rVal;
//        CExpression * lVal;
//        do {
//            rVal = exprStack.top(); exprStack.pop();
//            lVal = exprStack.top(); exprStack.pop();
//
//            p = new CAddExp(lVal, rVal);
//            exprStack.push(p);
//
//        } while(exprStack.size() != 1);
//
//        CBigNum product = exprStack.top()->evaluate();
//        if(m_sgn && !other.m_sgn || !m_sgn && other.m_sgn)
//            product.operator-();
//        return product;
//    }

    CExpression * rVal;
    CExpression * lVal;
    CExpression * sum;

    while(exprStack.size() != 1) {
        rVal = exprStack.top(); exprStack.pop();
        lVal = exprStack.top(); exprStack.pop();

        sum = new CAddExp(lVal, rVal);
        exprStack.push(sum);
    }

    CBigNum product = exprStack.top()->evaluate();
    return product;
}

std::string CBigNum::toString(uint32_t num) const
{
    std::stringstream ss;
    ss << std::setw(9) << std::setfill('0') << num;
    return ss.str();
}
