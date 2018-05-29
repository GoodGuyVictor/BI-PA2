//
// Created by victor on 26.5.18.
//

#include <iomanip>
#include "CVariable.h"

CVariable::CVariable(const std::string &name, const CBigNum &val)
{
    m_name = name;
    m_value = val;
}

CBigNum CVariable::evaluate() const
{
    return m_value;
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
    CExpression *tmp = new CVariable(m_name, m_value);
    return tmp;
}

std::string CVariable::toString() const
{
    std::string result;

    result = m_name;
    result += "=";
    result += m_value.toString();

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

void CVariable::setValue(const CBigNum & value)
{
    m_value = value;
}
