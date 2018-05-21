//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CLONGINTEGER_H
#define SEMESTRALKA_CLONGINTEGER_H

#include <algorithm>
#include "CExpression.h"

class CLongInteger : public CExpression
{
public:
    CLongInteger(std::string val)
    {
        if(val[0] == '-') {
            m_sgn = true;
            val.erase(0,1);
        } else
            m_sgn = false;
        m_value = toBigInt(val);
    }
    CBigNum evaluate() const override ;

private:
    bool m_sgn;
    std::vector<uint32_t> m_value;

    std::vector<uint32_t> toBigInt(std::string &);
};

std::vector<uint32_t> CLongInteger::toBigInt(std::string & text)
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

    ss << text;
    ss >> tmp;
    result.push_back(tmp);

    return result;
}

CBigNum CLongInteger::evaluate() const
{
    return CBigNum(m_sgn, m_value);
}

#endif //SEMESTRALKA_CLONGINTEGER_H
