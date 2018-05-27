//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CVARIABLE_H
#define SEMESTRALKA_CVARIABLE_H

#include <string>
#include "Expression.h"

class CVariable : public Expression
{
public:
    CVariable (const std::string &name, const std::string & val);
    CVariable (const std::string &name, bool, const std::vector<uint32_t> &, const std::vector<uint32_t> &);

    CBigNum evaluate() const override;
    std::string getName() const;
    Expression * clone() const;

private:
    std::string m_name;
    bool m_sgn;
    std::vector<uint32_t> m_exponent;
    std::vector<uint32_t> m_fraction;

    std::vector<uint32_t> toBigInt(std::string text) const;
};

#endif //SEMESTRALKA_CVARIABLE_H
