//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CINTEGER_H
#define SEMESTRALKA_CINTEGER_H

#include <sstream>
#include "CExpression.h"

class CInteger : public CExpression
{
public:
    explicit    CInteger   (const std::string & val);

    CBigNum     evaluate   () const override ;

private:
    int m_value;
};



#endif //SEMESTRALKA_CINTEGER_H
