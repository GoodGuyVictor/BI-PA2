//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBINOPERATOR_H
#define SEMESTRALKA_CBINOPERATOR_H

#include "CExpression.h"

/*! @class CBinOperator
 *  @brief The class simulates binary operations
 *
 */

class CBinOperator : public CExpression
{
public:
    /**
     * Constructor
     * @param l left hand operand
     * @param r right hand operand
     * all parameters allocated dynamically
     */
    CBinOperator(CExpression * l, CExpression * r)
            : m_lVal(l), m_rVal(r) {};
    /**
     * Destructor
     * Frees up allocated parameters
     */
    ~CBinOperator()
    {
        delete m_lVal;
        delete m_rVal;
    };

protected:
    /** left hand operand */
    CExpression * m_lVal;
    /** right hand operand */
    CExpression * m_rVal;
};

#endif //SEMESTRALKA_CBINOPERATOR_H
