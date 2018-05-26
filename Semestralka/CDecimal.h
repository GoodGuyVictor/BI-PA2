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
    explicit    CDecimal    (const std::string & value);

    CBigNum     evaluate    () const override ;

private:
    bool m_sgn;
    std::vector<uint32_t> m_exponent;
    std::vector<uint32_t> m_fraction;

    std::vector<uint32_t> toBigInt(std::string & text) const;
};


#endif //SEMESTRALKA_CDECIMAL_H
