//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDECIMAL_H
#define SEMESTRALKA_CDECIMAL_H

#include <string>
#include <sstream>
#include "Expression.h"

class Decimal : public Expression
{
public:
    explicit    Decimal    (const std::string & value);

    CBigNum     evaluate    () const override ;

private:
    bool m_sgn;
    std::vector<uint32_t> m_exponent;
    std::vector<uint32_t> m_fraction;

    std::vector<uint32_t> toBigInt(std::string & text) const;
};


#endif //SEMESTRALKA_CDECIMAL_H
