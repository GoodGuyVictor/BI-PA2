//
// Created by victor on 23.5.18.
//

#include "SubtractExp.h"

CBigNum SubtractExp::evaluate() const
{
    return m_lVal->evaluate() - m_rVal->evaluate();
}