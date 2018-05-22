//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CSUBTRACTEXP_H
#define SEMESTRALKA_CSUBTRACTEXP_H

#include "CBinOperator.h"

class CSubtractExp : public CBinOperator
{
public:
    CSubtractExp(CExpression * l, CExpression * r) : CBinOperator(l, r) {};
    CBigNum evaluate() const override ;
};

CBigNum CSubtractExp::evaluate() const
{
    return m_lVal->evaluate() - m_rVal->evaluate();
}

#endif //SEMESTRALKA_CSUBTRACTEXP_H
