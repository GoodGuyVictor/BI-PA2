//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CLONGINTEGER_H
#define SEMESTRALKA_CLONGINTEGER_H

#include "CExpression.h"

class CLongInteger : public CExpression
{
public:
    CLongInteger(std::string val)
    {
        if(val[0] == '-') {
            m_sgn = true;
            val.erase(0);
        } else
            m_sgn = false;
        m_value = toBigInt(val);
    }
    CBigNum evaluate() const override ;

private:
    bool m_sgn;
    std::vector<uint32_t> m_value;

    std::vector<uint32_t> toBigInt(std::string &);
};

std::vector<uint32_t> CLongInteger::toBigInt(std::string & text)
{
    // convert string to BCD-like
    for (char &c : text) c -= '0';
    // build result vector
    std::vector<uint32_t> value(1, 0);
    uint32_t bit = 1;
    for (;;) {
        // set next bit if last digit is odd
        if (text.back() & 1) value.back() |= bit;
        // divide BCD-like by 2
        bool notNull = false; int carry = 0;
        for (char &c : text) {
            const int carryNew = c & 1;
            c /= 2; c += carry * 5;
            carry = carryNew;
            notNull |= c;
        }
        if (!notNull) break;
        // shift bit
        bit <<= 1;
        if (!bit) {
            value.push_back(0); bit = 1;
        }
    }
    // done
    return value;
}

CBigNum CLongInteger::evaluate() const
{
    return CBigNum(m_sgn, m_value);
}

#endif //SEMESTRALKA_CLONGINTEGER_H
