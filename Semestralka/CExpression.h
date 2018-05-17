//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CEXPRESSION_H
#define SEMESTRALKA_CEXPRESSION_H

#include "CBigNum.h"

class CExpression
{
public:
    CExpression() = default;
    virtual ~CExpression() = default;

    virtual CBigNum evaluate() const = 0;
};


#endif //SEMESTRALKA_CEXPRESSION_H
