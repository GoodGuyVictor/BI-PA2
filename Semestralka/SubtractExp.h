//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CSUBTRACTEXP_H
#define SEMESTRALKA_CSUBTRACTEXP_H

#include "BinOperator.h"

class SubtractExp : public BinOperator
{
public:
            SubtractExp    (Expression * l, Expression * r)
                    : BinOperator(l, r) {};

    CBigNum evaluate        () const override ;
};


#endif //SEMESTRALKA_CSUBTRACTEXP_H
