//
// Created by victor on 23.5.18.
//

#include "CDecimal.h"

CDecimal::CDecimal(const std::string & val)
{
    std::string value(val);
    if(value[0] == '-') {
        m_sgn = true;
        value.erase(0,1);
    } else
        m_sgn = false;

    char * token;
    token = strtok((char*)value.c_str(), ".");
    std::string exponent(token);
    token = strtok(NULL, ".");
    std::string fraction(token);

    m_integer = toBigInt(exponent);
    m_fraction = toBigInt(fraction);
}

CBigNum CDecimal::evaluate() const
{
    return CBigNum(m_sgn, m_integer, m_fraction);
}

std::vector<uint32_t> CDecimal::toBigInt(std::string & value) const
{
    std::vector<uint32_t> result;
    int len = value.size();
    int portions = len / 9;
    std::stringstream ss;
    uint32_t tmp;

    for(int i = 0; i < portions; i++) {
        ss << value.substr(value.size() - 9, 9);
        ss >> tmp;
        result.push_back(tmp);
        value.erase(value.size() - 9, 9);
        ss.clear();
    }

    if(!value.empty()) {
        ss << value;
        ss >> tmp;
        result.push_back(tmp);
    }

    return result;
}