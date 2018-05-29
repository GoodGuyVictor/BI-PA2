//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBIGNUM_H
#define SEMESTRALKA_CBIGNUM_H

#include <sstream>
#include <algorithm>
#include <cstring>
#include <cstdint>
#include <stdint-gcc.h>

/*! @class CBigNum
 *  @brief The class represents highly accurate number of any size
 *
 */
class CBigNum
{
public:
    /**
     * @brief Default constructor creates number with zero value
     */
                CBigNum     ();
    /**
     * @brief Constructor translates usual int value into CBigNum
     * @param val integer number
     */
    explicit    CBigNum     (int val);
    /**
     * @brief Constructor creates one big number out of array of values, fractional part is set to zero
     * @param sgn Presence of minus before the value
     * @param integer vector of uint32_t values integer part of the number
     */
                CBigNum     (bool sgn, const std::vector<uint32_t > & integer);
    /**
     * @brief Constructor creates one big number out of arrays of values with fractional part included
     * @param sgn Presence of minus before the value
     * @param integer vector of uint32_t values integer part of the number
     * @param fraction vector of uint32_t values fractional part of the number
     */
                CBigNum     (bool sgn, const std::vector<uint32_t > & integer, const std::vector<uint32_t> & fraction);

    void            print           () const;
    CBigNum         operator+       (const CBigNum &) const;
    CBigNum         operator-       (const CBigNum &) const;
    CBigNum         operator-       () const;
    CBigNum         operator*       (const CBigNum &) const;
    CBigNum         operator/       (const CBigNum &) const;
    CBigNum         operator%       (const CBigNum &) const;
    bool            operator>=      (const CBigNum &) const;
    std::string     toString        () const;

private:
    std::vector<uint32_t>   m_exponent;
    std::vector<uint32_t>   m_fraction;
    bool                    m_sgn;

    std::vector<uint32_t>       additionAlgorithm           (const std::vector<uint32_t> &, const std::vector<uint32_t> &, unsigned short &) const;
    std::vector<uint32_t>       subtractionAlgorithm        (const std::vector<uint32_t> &, const std::vector<uint32_t> &, unsigned short &, bool &) const;
    CBigNum                     multiplicationAlgorithm     (const std::vector<uint32_t> &, const std::vector<uint32_t> &) const;
    void                        divisionAlgorithm           (const std::vector<uint32_t> &, const std::vector<uint32_t> &, std::string &, std::string &) const;
    std::vector<uint32_t>       addFractions                (std::vector<uint32_t> &, std::vector<uint32_t> &, unsigned short &) const;
    std::vector<uint32_t>       subtractFractions           (std::vector<uint32_t> &, std::vector<uint32_t> &, unsigned short &) const;

    void                        multiplyByTen               ();
    void                        expandFewerNumberWithZeros  (std::vector<uint32_t> &, std::vector<uint32_t> &) const;
    std::string                 toString                    (const std::vector<uint32_t> &) const;
    std::string                 toString                    (const CBigNum &) const;
    std::string                 toString                    (uint32_t, bool = true) const;
    int                         eliminateEndingZeros        (std::vector<uint32_t> &, std::vector<uint32_t> &) const;
    std::vector<uint32_t>       toBigInt                    (std::string text) const;
    void                        modulo                      (std::vector<uint32_t> &) const;
    bool                        isZero                      (const std::vector<uint32_t> &) const;
};

#endif //SEMESTRALKA_CBIGNUM_H
