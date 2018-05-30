//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CVARIABLE_H
#define SEMESTRALKA_CVARIABLE_H

#include <string>
#include "CExpression.h"

/*! @class CVariable
 *  @brief The class represents variable that can contain any number
 *
 */
class CVariable : public CExpression
{
public:
    /**
     * Constructor creates new variable with name and value
     * @param name Variable name
     * @param val Variable value
     */
    CVariable (const std::string &name, const CBigNum &val);

    /**
     * Translates variable value into CBigNum
     * @return
     */
    CBigNum evaluate() const override;
    /**
     * Gets varuable name
     * @return Veriable name
     */
    std::string getName() const;
    /**
     * Creates deep copy of variable
     * @return Pointer to dynamic copy of current variable type CExpression
     */
    CExpression * clone() const;
    /**
     * Translates variable value into string
     * @return String representation of variable value
     */
    std::string toString() const;
    /**
     * Sets variable value
     * @param value Object of CBigNum to be set as vriable value
     */
    void setValue(const CBigNum & value);
private:
    /** Variable name */
    std::string m_name;
    /** Variable value */
    CBigNum m_value;
    /**
     * Translates string value into vector of uint32_t's
     * @param value The value to be translated
     * @return Vector of uint32_t's
     */
    std::vector<uint32_t> toBigInt(std::string value) const;
    /**
     * Translates number contained in vector of uint32_t's to string
     * @param value Long number to be translated
     * @return String representation of a long number
     */
    std::string toString(const std::vector<uint32_t> & value) const;
};

#endif //SEMESTRALKA_CVARIABLE_H
