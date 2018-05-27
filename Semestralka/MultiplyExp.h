//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CMULTIPLYEXP_H
#define SEMESTRALKA_CMULTIPLYEXP_H

#include "BinOperator.h"

class CMultiplyExp : public BinOperator
{
public:
    CMultiplyExp(Expression * l, Expression * r) : BinOperator(l, r) {};
    CBigNum evaluate() const override ;
};

#endif //SEMESTRALKA_CMULTIPLYEXP_H
