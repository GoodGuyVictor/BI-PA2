//
// Created by victor on 22.5.18.
//

#include "MultiplyExp.h"

CBigNum CMultiplyExp::evaluate() const
{
    return m_lVal->evaluate() * m_rVal->evaluate();
}