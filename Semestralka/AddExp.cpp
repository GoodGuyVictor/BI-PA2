//
// Created by victor on 22.5.18.
//

#include "AddExp.h"

CBigNum CAddExp::evaluate() const
{
    return m_lVal->evaluate() + m_rVal->evaluate();
}