//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CADDEXP_H
#define SEMESTRALKA_CADDEXP_H

#include "BinOperator.h"

class CAddExp : public BinOperator
{
public:
            CAddExp     (Expression * l, Expression * r)
                    : BinOperator(l, r) {};

    CBigNum evaluate    () const override ;
};

#endif //SEMESTRALKA_CADDEXP_H
