//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDECIMAL_H
#define SEMESTRALKA_CDECIMAL_H

#include <string>
#include <sstream>
#include "CExpression.h"

class CDecimal : public CExpression
{
public:
    explicit    CDecimal    (const std::string & val);

    CBigNum     evaluate    () const override ;

private:
    double m_value;
};


#endif //SEMESTRALKA_CDECIMAL_H
