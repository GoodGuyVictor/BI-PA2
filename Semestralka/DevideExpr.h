//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDEVIDEEXPR_H
#define SEMESTRALKA_CDEVIDEEXPR_H

#include "BinOperator.h"

class CDevideExp : public BinOperator
{
public:
            CDevideExp  (Expression * l, Expression * r)
                    : BinOperator(l, r) {};
    CBigNum evaluate    () const override ;
};

#endif //SEMESTRALKA_CDEVIDEEXPR_H
