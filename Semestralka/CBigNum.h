//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBIGNUM_H
#define SEMESTRALKA_CBIGNUM_H

#include <sstream>
#include <algorithm>
#include <cstring>

class CBigNum
{
public:
                CBigNum     ()
                        : m_sgn(false), m_fraction(0);
    explicit    CBigNum     (int val);
    explicit    CBigNum     (double val);
                CBigNum     (bool sgn, const std::vector<uint32_t > & val);

    void            print           () const;
    CBigNum &       operator+       (const CBigNum & other);
    CBigNum &       operator-       (const CBigNum & other);
    CBigNum &       operator-       ();
    CBigNum         operator*       (const CBigNum & other);

private:
    std::vector<uint32_t>   m_exponent;
    uint32_t                m_fraction;
    bool                    m_sgn;

    uint32_t        addFractions                (uint32_t f1, uint32_t f2, unsigned short & carry) const;
    uint32_t        subtractFractions           (uint32_t f1, uint32_t f2, unsigned short & carry);
    unsigned short  getCarry                    (const uint32_t sum) const;
    void            expandFewerNumberWithZeros  (std::vector<uint32_t> & exponent1, std::vector<uint32_t> & exponent2);
};

#endif //SEMESTRALKA_CBIGNUM_H
