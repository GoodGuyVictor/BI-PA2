//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CADDEXP_H
#define SEMESTRALKA_CADDEXP_H

#include "CBinOperator.h"

/*! @class CAddExp
 *  @brief The class represents expression that performs addition operation. Child class of CExpression.
 */
class CAddExp : public CBinOperator
{
public:
 /**
  * Constructor creates new addition expression
  * @param l Left hand operand
  * @param r Right hand operand
  */
            CAddExp     (CExpression * l, CExpression * r)
                    : CBinOperator(l, r) {};

    /**
     * Evaluates the sum of two expressions
     * @return Highly accurate number
     */
    CBigNum evaluate    () const override ;
};

#endif //SEMESTRALKA_CADDEXP_H
