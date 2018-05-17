//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBINOPERATOR_H
#define SEMESTRALKA_CBINOPERATOR_H

#include "CExpression.h"

class CBinOperator : public CExpression
{
public:
    CBinOperator(CExpression * l, CExpression * r) : m_lVal(l), m_rVal(r) {};
    ~CBinOperator()
    {
        delete m_lVal;
        delete m_rVal;
    };

protected:
    CExpression * m_lVal;
    CExpression * m_rVal;
};

#endif //SEMESTRALKA_CBINOPERATOR_H
