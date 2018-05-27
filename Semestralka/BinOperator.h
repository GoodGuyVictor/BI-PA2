//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBINOPERATOR_H
#define SEMESTRALKA_CBINOPERATOR_H

#include "Expression.h"

class BinOperator : public Expression
{
public:
    BinOperator(Expression * l, Expression * r)
            : m_lVal(l), m_rVal(r) {};
    ~BinOperator()
    {
        delete m_lVal;
        delete m_rVal;
    };

protected:
    Expression * m_lVal;
    Expression * m_rVal;
};

#endif //SEMESTRALKA_CBINOPERATOR_H
