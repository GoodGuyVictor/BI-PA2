//
// Created by victor on 25.5.18.
//

#include "CMod.h"

CBigNum CMod::evaluate() const {
    return m_lVal->evaluate() % m_rVal->evaluate();
}
