//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CLONGINTEGER_H
#define SEMESTRALKA_CLONGINTEGER_H

#include "CExpression.h"

class CLongInteger : public CExpression
{
public:
    CLongInteger(const std::string & val)
    {
        std::stringstream ss;
        ss << val;
        ss >> m_value;
    }
    CBigNum evaluate() const override ;

private:
    bool m_sgn;
    std::vector<uint32_t> m_value;
};

#endif //SEMESTRALKA_CLONGINTEGER_H
