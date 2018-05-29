//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CEXPRESSION_H
#define SEMESTRALKA_CEXPRESSION_H

#include "CBigNum.h"


/*! @class CExpression
 *  @brief Abstract class represents numbers, variables and binary operations
 *
 */
class CExpression
{
public:
    /**
     * Default constructor
     */
    CExpression() = default;
    /**
     * Virtual destructor
     */
    virtual ~CExpression() = default;
    /**
     * Virtual method evaluate, evaluates given expression
     * @return Outcome is an instance of CBigNum
     */
    virtual CBigNum evaluate() const = 0;
};


#endif //SEMESTRALKA_CEXPRESSION_H
