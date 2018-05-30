//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDECIMAL_H
#define SEMESTRALKA_CDECIMAL_H

#include <string>
#include <sstream>
#include "CExpression.h"

/*! @class CDecimal
 *  @brief The class represents decimal number. Child class of CExpression.
 */
class CDecimal : public CExpression
{
public:
    /**
     * Constructor creates decimal object
     * @param value String value to be translated into CDecimal
     */
    explicit    CDecimal    (const std::string & value);
    /**
     * Converts CDecimal into CBigNum
     * @return CBigNum object
     */
    CBigNum     evaluate    () const override ;

private:
    /** Presence of minus */
    bool m_sgn;
    /** Integer part of decimal number */
    std::vector<uint32_t> m_integer;
    /** Fractoin part of decimal number */
    std::vector<uint32_t> m_fraction;
    /**
     * Translates string value into vector of uint32_t's
     * @param value String value to be translated
     * @return Vector of uint32_t's
     */
    std::vector<uint32_t> toBigInt(std::string & value) const;
};


#endif //SEMESTRALKA_CDECIMAL_H
