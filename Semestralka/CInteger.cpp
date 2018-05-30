//
// Created by victor on 22.5.18.
//

#include "CInteger.h"

CInteger::CInteger(const std::string &value)
{
    std::stringstream ss;
    ss << value;
    ss >> m_value;
}

CBigNum CInteger::evaluate() const
{
    return CBigNum(m_value);
}
