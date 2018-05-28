//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CVARIABLE_H
#define SEMESTRALKA_CVARIABLE_H

#include <string>
#include "CExpression.h"

class CVariable : public CExpression
{
public:
    CVariable (const std::string &name, const CBigNum &val);

    CBigNum evaluate() const override;
    std::string getName() const;
    CExpression * clone() const;
    std::string toString() const;
    void setValue(const CBigNum &);
private:

    std::string m_name;
    CBigNum m_value;

    std::vector<uint32_t> toBigInt(std::string text) const;
    std::string toString(const std::vector<uint32_t> &) const;
};

#endif //SEMESTRALKA_CVARIABLE_H
