//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CINTEGER_H
#define SEMESTRALKA_CINTEGER_H

#include <sstream>
#include "Expression.h"

class CInteger : public Expression
{
public:
    explicit    CInteger   (const std::string & val);

    CBigNum     evaluate   () const override ;

private:
    int m_value;
};



#endif //SEMESTRALKA_CINTEGER_H
