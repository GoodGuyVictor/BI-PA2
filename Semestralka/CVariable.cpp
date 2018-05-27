//
// Created by victor on 26.5.18.
//

#include <iomanip>
#include "CVariable.h"

CVariable::CVariable(const std::string &name, const std::string &val)
        : m_name(name)
{
    std::string value(val);
    if(value[0] == '-') {
        m_sgn = true;
        value.erase(0,1);
    } else
        m_sgn = false;

    if(val.find('.') != std::string::npos) {
        char * token;
        token = strtok((char*)value.c_str(), ".");
        std::string exponent(token);
        token = strtok(NULL, ".");
        std::string fraction(token);
        m_exponent = toBigInt(exponent);
        m_fraction = toBigInt(fraction);
    } else {
        m_exponent = toBigInt(val);
        m_fraction.push_back(0);
    }
}

CBigNum CVariable::evaluate() const
{
    return CBigNum(m_sgn, m_exponent, m_fraction);
}

std::vector<uint32_t> CVariable::toBigInt(std::string text) const
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

std::string CVariable::getName() const
{
    return m_name;
}

CExpression *CVariable::clone() const
{
    CExpression *tmp = new CVariable(m_name, m_sgn, m_exponent, m_fraction);
    return tmp;
}

CVariable::CVariable(const std::string &name, bool sgn, const std::vector<uint32_t> & exponent, const std::vector<uint32_t> & fraction)
: m_name(name), m_sgn(sgn)
{
    m_exponent = exponent;
    m_fraction = fraction;
}

std::string CVariable::toString() const
{
    std::string result;

    result = m_name;
    result += " = ";
    if(m_sgn)
        result += "-";
    result += toString(m_exponent);
    std::string fraction = toString(m_fraction);
    if(fraction != "0") {
        result += ".";
        result += fraction;
    }
    return result;
}

std::string CVariable::toString(const std::vector<uint32_t> & value) const
{
    std::stringstream ss;
    for(auto it = value.rbegin(); it < value.rend(); it++)
        if(it == value.rbegin())
            ss << *it;
        else
            ss << std::setw(9) << std::setfill('0') << *it;
    std::string result;
    ss >> result;
    return result;
}
