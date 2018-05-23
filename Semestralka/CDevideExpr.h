//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDEVIDEEXPR_H
#define SEMESTRALKA_CDEVIDEEXPR_H

#include "CBinOperator.h"

class CDevideExp : public CBinOperator
{
public:
    CDevideExp(CExpression * l, CExpression * r) : CBinOperator(l, r) {};
    CBigNum evaluate() const override ;
};

CBigNum CDevideExp::evaluate() const {

}

#endif //SEMESTRALKA_CDEVIDEEXPR_H
