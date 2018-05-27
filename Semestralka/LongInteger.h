//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CLONGINTEGER_H
#define SEMESTRALKA_CLONGINTEGER_H

#include <algorithm>
#include "Expression.h"

class CLongInteger : public Expression
{
public:
    explicit    CLongInteger    (std::string val);
    CBigNum     evaluate        () const override ;

private:
    bool                    m_sgn;
    std::vector<uint32_t>   m_value;

    std::vector<uint32_t>   toBigInt(std::string &);
};





#endif //SEMESTRALKA_CLONGINTEGER_H
