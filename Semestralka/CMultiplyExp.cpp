//
// Created by victor on 22.5.18.
//

#include "CMultiplyExp.h"

CBigNum CMultiplyExp::evaluate() const
{
    return m_lVal->evaluate() * m_rVal->evaluate();
}