//
// Created by victor on 25.5.18.
//

#include "CModExp.h"

CBigNum CModExp::evaluate() const
{
    return m_lVal->evaluate() % m_rVal->evaluate();
}
