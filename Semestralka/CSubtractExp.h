//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CSUBTRACTEXP_H
#define SEMESTRALKA_CSUBTRACTEXP_H

#include "CBinOperator.h"

/*! @class CSubtractExp
 *  @brief The class represents expression that performs subtraction operation. Child class of CExpression.
 */
class CSubtractExp : public CBinOperator
{
public:
      /**
      * Constructor creates new subtraction expression
      * @param l Left hand operand
      * @param r Right hand operand
      */
            CSubtractExp    (CExpression * l, CExpression * r)
                    : CBinOperator(l, r) {};
    /**
     * Evaluates the difference of two expressions
     * @return Highly accurate number
     */
    CBigNum evaluate        () const override ;
};


#endif //SEMESTRALKA_CSUBTRACTEXP_H
