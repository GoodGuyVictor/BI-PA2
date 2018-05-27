//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CEXPRESSION_H
#define SEMESTRALKA_CEXPRESSION_H

#include "BigNum.h"

class Expression
{
public:
    Expression() = default;
    virtual ~Expression() = default;

    virtual CBigNum evaluate() const = 0;
};


#endif //SEMESTRALKA_CEXPRESSION_H
