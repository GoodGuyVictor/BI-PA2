//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CINTEGER_H
#define SEMESTRALKA_CINTEGER_H

#include <sstream>
#include "CExpression.h"

/*! @class CInteger
 *  @brief The class represents integer number. Child class of CExpression.
 */
class CInteger : public CExpression
{
public:
    /**
     * Cpnstructor creates integer object
     * @param value String value to be translated into CInteger
     */
    explicit    CInteger   (const std::string & value);
    /**
     * Translates CInteger into CBigNum
     * @return CBigNum object
     */
    CBigNum     evaluate   () const override ;

private:
    /** Signed integer value */
    int m_value;
};



#endif //SEMESTRALKA_CINTEGER_H
