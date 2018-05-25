//
// Created by victor on 25.5.18.
//

#ifndef SEMESTRALKA_CMOD_H
#define SEMESTRALKA_CMOD_H


#include "CBinOperator.h"

class CMod : public CBinOperator
{
public:
            CMod        (CExpression * lVal, CExpression * rVal)
            : CBinOperator(lVal, rVal) {}

    CBigNum evaluate    () const override;
};


#endif //SEMESTRALKA_CMOD_H
