//
// Created by victor on 22.5.18.
//

#include "CAddExp.h"

CBigNum CAddExp::evaluate() const
{
    return m_lVal->evaluate() + m_rVal->evaluate();
}