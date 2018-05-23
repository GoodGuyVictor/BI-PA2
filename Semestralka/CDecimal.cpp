//
// Created by victor on 23.5.18.
//

#include "CDecimal.h"

CDecimal::CDecimal(const std::string &val)
{
    std::stringstream ss;
    ss << val;
    ss >> m_value;
}

CBigNum CDecimal::evaluate() const
{
    return CBigNum(m_value);
}
