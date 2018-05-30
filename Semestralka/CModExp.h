//
// Created by victor on 25.5.18.
//

#ifndef SEMESTRALKA_CMOD_H
#define SEMESTRALKA_CMOD_H


#include "CBinOperator.h"

/*! @class CMod
 *  @brief The class represents expression that performs division operation taking raminder only and discards
 *  quotient. Child class of CExpression.
 *
 */
class CModExp : public CBinOperator
{
public:
    /**
    * Constructor creates division expression
    * @param l Left hand operand
    * @param r Right hand operand
    */
            CModExp        (CExpression * lVal, CExpression * rVal)
            : CBinOperator(lVal, rVal) {}
    /**
    * Evaluates the division operation
    * @return Remainder of the division represented as CBigNum
    */
    CBigNum evaluate    () const override;
};


#endif //SEMESTRALKA_CMOD_H
