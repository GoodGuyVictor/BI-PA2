//
// Created by victor on 25.5.18.
//

#include "Mod.h"

CBigNum CMod::evaluate() const
{
    return m_lVal->evaluate() % m_rVal->evaluate();
}
