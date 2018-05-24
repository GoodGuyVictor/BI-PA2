//
// Created by victor on 23.5.18.
//

#include "CSubtractExp.h"

CBigNum CSubtractExp::evaluate() const
{
    return m_lVal->evaluate() - m_rVal->evaluate();
}