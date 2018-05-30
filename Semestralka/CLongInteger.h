//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CLONGINTEGER_H
#define SEMESTRALKA_CLONGINTEGER_H

#include <algorithm>
#include "CExpression.h"

/*! @class CLongInteger
 *  @brief The class represents long integer number. Child class of CExpression.
 */
class CLongInteger : public CExpression
{
public:
    /**
     * Constructor creates long integer object
     * @param value String value to be translated into CLongInteger
     */
    explicit    CLongInteger    (std::string value);
    /**
     * Translates CLongInteger into CBigNum
     * @return CBigNum object
     */
    CBigNum     evaluate        () const override ;

private:
    /** Presence of minus */
    bool                    m_sgn;
    /** Huge integer number placed into vector of uint32_t's */
    std::vector<uint32_t>   m_value;
    /**
     * Translates string value into vector of uint32_t's
     * @param value String value to be translated
     * @return Vector of uint32_t's
     */
    std::vector<uint32_t>   toBigInt(std::string & value);
};

#endif //SEMESTRALKA_CLONGINTEGER_H
