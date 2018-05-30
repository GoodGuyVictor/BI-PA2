//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CMULTIPLYEXP_H
#define SEMESTRALKA_CMULTIPLYEXP_H

#include "CBinOperator.h"

/*! @class CMultiplyExp
 *  @brief The class represents expression that performs multiplication operation. Child class of CExpression.
 */
class CMultiplyExp : public CBinOperator
{
public:
    /**
     * Constructor creates new multiplication expression
     * @param l Left hand operand
     * @param r Right hand operand
     */
    CMultiplyExp(CExpression * l, CExpression * r) : CBinOperator(l, r) {};
    /**
     * Evaluates the product of two expressions
     * @return Highly accurate number
     */
    CBigNum evaluate() const override ;
};

#endif //SEMESTRALKA_CMULTIPLYEXP_H
