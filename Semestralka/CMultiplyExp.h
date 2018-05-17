//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CMULTIPLYEXP_H
#define SEMESTRALKA_CMULTIPLYEXP_H

#include "CBinOperator.h"

class CMultiplyExp : public CBinOperator
{
public:
    CMultiplyExp(CExpression * l, CExpression * r) : CBinOperator(l, r) {};
    CBigNum evaluate() const override ;
};

#endif //SEMESTRALKA_CMULTIPLYEXP_H
