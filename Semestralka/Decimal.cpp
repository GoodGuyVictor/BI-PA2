//
// Created by victor on 23.5.18.
//

#include "Decimal.h"

Decimal::Decimal(const std::string & val)
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

    m_exponent = toBigInt(exponent);
    m_fraction = toBigInt(fraction);
}

CBigNum Decimal::evaluate() const
{
    return CBigNum(m_sgn, m_exponent, m_fraction);
}

std::vector<uint32_t> Decimal::toBigInt(std::string & text) const
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