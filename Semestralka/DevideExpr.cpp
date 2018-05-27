//
// Created by victor on 23.5.18.
//

#include "DevideExpr.h"

CBigNum CDevideExp::evaluate() const
{
    return m_lVal->evaluate() / m_rVal->evaluate();
}
