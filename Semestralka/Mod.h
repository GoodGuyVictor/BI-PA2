//
// Created by victor on 25.5.18.
//

#ifndef SEMESTRALKA_CMOD_H
#define SEMESTRALKA_CMOD_H


#include "BinOperator.h"

class CMod : public BinOperator
{
public:
            CMod        (Expression * lVal, Expression * rVal)
            : BinOperator(lVal, rVal) {}

    CBigNum evaluate    () const override;
};


#endif //SEMESTRALKA_CMOD_H
