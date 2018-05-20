//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CADDEXP_H
#define SEMESTRALKA_CADDEXP_H

#include "CBinOperator.h"

class CAddExp : public CBinOperator
{
public:
    CAddExp(CExpression * l, CExpression * r) : CBinOperator(l, r) {};
    CBigNum evaluate() const override ;
};

CBigNum CAddExp::evaluate() const
{
    return m_lVal->evaluate() + m_rVal->evaluate();
}

#endif //SEMESTRALKA_CADDEXP_H
