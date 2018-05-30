//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CDEVIDEEXPR_H
#define SEMESTRALKA_CDEVIDEEXPR_H

#include "CBinOperator.h"

/*! @class CDevideExp
 *  @brief The class represents expression that performs division operation taking quotient only and discards
 *  remainder. Child class of CExpression.
 *
 */
class CDevideExp : public CBinOperator
{
public:
    /**
     * Constructor creates division expression
     * @param l Left hand operand
     * @param r Right hand operand
     */
            CDevideExp  (CExpression * l, CExpression * r)
                    : CBinOperator(l, r) {};
    /**
     * Evaluates the division operation
     * @return Quotient of the division represented as CBigNum
     */
    CBigNum evaluate    () const override ;
};

#endif //SEMESTRALKA_CDEVIDEEXPR_H
