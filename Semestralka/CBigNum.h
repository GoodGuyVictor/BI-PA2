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
                        : m_sgn(false), m_fraction(0) {};
    explicit    CBigNum     (int val);
    explicit    CBigNum     (double val);
                CBigNum     (bool sgn, const std::vector<uint32_t > &, const uint32_t = 0);

    void            print           () const;
    CBigNum         operator+       (const CBigNum &) const;
    CBigNum         operator-       (const CBigNum &) const;
    CBigNum         operator-       () const;
    CBigNum         operator*       (const CBigNum &) const;
    CBigNum         operator/       (const CBigNum &) const;
    CBigNum         operator%       (const CBigNum &) const;
    bool            operator>=      (const CBigNum &) const;

private:
    std::vector<uint32_t>   m_exponent;
    uint32_t                m_fraction;
    bool                    m_sgn;

    uint32_t        addFractions                (uint32_t, uint32_t, unsigned short &) const;
    uint32_t        subtractFractions           (uint32_t, uint32_t, unsigned short &) const;
    unsigned short  getCarry                    (const uint32_t) const;
    void            expandFewerNumberWithZeros  (std::vector<uint32_t> &, std::vector<uint32_t> &) const;
    std::string     toString                    (const std::vector<uint32_t> &) const;
    std::string     toString                    (const CBigNum &) const;
    std::string     toString                    (uint32_t) const;
    void            divideAlgorithm             (const std::vector<uint32_t> &,
                                                 const std::vector<uint32_t> &,
                                                 std::string &, std::string &) const;
    void            multiplyByTen               ();
    int            eliminateEndingZeros         (std::vector<uint32_t> &, std::vector<uint32_t> &) const;
    std::vector<uint32_t> toBigInt              (std::string & text) const;
    CBigNum         multiplicationAlgorithm     (const std::vector<uint32_t> &,
                                                 const std::vector<uint32_t> &) const;
};

#endif //SEMESTRALKA_CBIGNUM_H
