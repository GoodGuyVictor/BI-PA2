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
     * Default constructor creates number with zero value
     */
                CBigNum     ();
    /**
     * Constructor translates usual int value into CBigNum
     * @param val integer number
     */
    explicit    CBigNum     (int val);
    /**
     * Constructor creates one big number out of array of values, fractional part is set to zero
     * @param sgn Presence of minus before the value
     * @param integer vector of uint32_t values integer part of the number
     */
                CBigNum     (bool sgn, const std::vector<uint32_t > & integer);
    /**
     * Constructor creates one big number out of arrays of values with fractional part included
     * @param sgn Presence of minus before the value
     * @param integer vector of uint32_t values integer part of the number
     * @param fraction vector of uint32_t values fractional part of the number
     */
                CBigNum     (bool sgn, const std::vector<uint32_t > & integer, const std::vector<uint32_t> & fraction);

    /**
     * @brief Print out the number on the screen
     */
    void            print           () const;
    /**
     * Adding up two highly accurate numbers
     * @param other Second summand
     * @return Sum of two highly accurate numbers
     */
    CBigNum         operator+       (const CBigNum & other) const;
    /**
     * Subtracting two highly accurate numbers
     * @param other The subtrahend
     * @return Difference of two highly accurate numbers
     */
    CBigNum         operator-       (const CBigNum & other) const;
    /**
     * Unary minus
     * @return Copy of negotiated this object
     */
    CBigNum         operator-       () const;
    /**
     * Multiplying two highly accurate numbers
     * @param other factor
     * @return Product of two highly accurate numbers
     */
    CBigNum         operator*       (const CBigNum & other) const;
    /**
     * Divide two highly accurate numbers
     * @param other Divisor
     * @return Quotient of division of two highly accurate numbers
     */
    CBigNum         operator/       (const CBigNum & other) const;
    /**
     * Divide two highly accurate numbers
     * @param other Dibisor
     * @return Remainder of division of two highly accurate numbers
     */
    CBigNum         operator%       (const CBigNum & other) const;
    /**
     * Comparison operator greater than or equal, compares two highly accurate numbers
     * @param other The number to compare with
     * @return true/false regarding the comparison
     */
    bool            operator>=      (const CBigNum & other) const;
    /**
     * Converts highly accurate number into string
     * @return string representation of CBighNum
     */
    std::string     toString        () const;

private:
    /** integer part of the number */
    std::vector<uint32_t>   m_integer;
    /** fractional part of the number */
    std::vector<uint32_t>   m_fraction;
    /** presence of minus */
    bool                    m_sgn;

    /**
     * Simple algorithm to add two numbers together represented as vector of uint32_t's considering carry (school math)
     * @param summand1 First summand
     * @param summand2 Second summand
     * @param carry carry is transmitted as a reference to set it for the next usages
     * @return Sum of two vectors
     */
    std::vector<uint32_t>       additionAlgorithm           (const std::vector<uint32_t> & summand1, const std::vector<uint32_t> & summand2, unsigned short & carry) const;
    /**
     * Simple algorithm to subtract two numbers represented as vector of uint32_t's considering carry
     * @param minuend The minuend
     * @param subtrahend The subtrahend
     * @param carry carry is transmitted as a reference to set it for the next usages
     * @param sgn presence of minus
     * @return Difference of two vectors
     */
    std::vector<uint32_t>       subtractionAlgorithm        (const std::vector<uint32_t> & minuend, const std::vector<uint32_t> & subtrahend, unsigned short & carry, bool & sgn) const;
    /**
     * Simple algorithm to multiply two numbers represented as vector of uint32_t's considering carry
     * @param factor1 First factor
     * @param factor2 Second factor
     * @return Highly accurate number, product of two vectors
     */
    CBigNum                     multiplicationAlgorithm     (const std::vector<uint32_t> & factor1, const std::vector<uint32_t> & factor2) const;
    /**
     * Simple division algorithm to divide two numbers represented as vector of uint32_t's
     * @param dividend The dividend
     * @param divisor The divisor
     * @param quotient Quotient reference
     * @param remainder Remainder reference
     */
    void                        divisionAlgorithm           (const std::vector<uint32_t> & dividend, const std::vector<uint32_t> & divisor, std::string & quotient, std::string & remainder) const;
    /**
     * Adds two fraction parts considering carry
     * @param f1 First fraction
     * @param f2 Second fraction
     * @param carry carry is transmitted as a reference to set it for the next usages
     * @return vector of unit32_t's
     */
    std::vector<uint32_t>       addFractions                (std::vector<uint32_t> & f1, std::vector<uint32_t> & f2, unsigned short & carry) const;
    /**
     * Subtracts two fraction considering carry
     * @param f1 First fractoin
     * @param f2 Second fraction
     * @param carry carry is transmitted as a reference to set it for the next usages
     * @return vector of uint32_t's
     */
    std::vector<uint32_t>       subtractFractions           (std::vector<uint32_t> & f1, std::vector<uint32_t> & f2, unsigned short & carry) const;
    /**
     * Multiplies current CBigNum by ten
     */
    void                        multiplyByTen               ();
    /**
     * Expands the shorter vector by setting zeros at its beginning to make it the same length as the longer one
     * @param integer1 Integer part of first highly accurate number
     * @param integer2 Integer part of second highly accurate number
     */
    void                        expandFewerNumberWithZeros  (std::vector<uint32_t> & integer1, std::vector<uint32_t> & integer2) const;
    /**
     * Translates number contained in vector of uint32_t's to string
     * @param value Long number to be translated
     * @return String representation of a long number
     */
    std::string                 toString                    (const std::vector<uint32_t> & value) const;
    /**
     * Translates highly accurate number into string
     * @param number The highly accurate number to be translated
     * @return String representation of highly accurate number
     */
    std::string                 toString                    (const CBigNum & number) const;
    /**
     * Translates number contained in vector of uint32_t's to string excluding or including leading zeros
     * @param num Long number to be stranslated
     * @param leadingZeros true - include leading zeros false - exclude leading zeros
     * @return String representation of a long number
     */
    std::string                 toString                    (uint32_t num, bool leadingZeros = true) const;
    /**
     * Delete zeros at the end of both numbers
     * @param integer1 First number
     * @param integer2 Second number
     * @return Number of deleted zeros
     */
    int                         eliminateEndingZeros        (std::vector<uint32_t> & integer1, std::vector<uint32_t> & integer2) const;
    /**
     * Translates string represented number into vector of uint32_t's
     * @param number Long number in text notation
     * @return vector of uint32_t's
     */
    std::vector<uint32_t>       toBigInt                    (std::string number) const;
    /**
     * Subtracts number from its modulo and replace the number by resulting value
     * @param num Number to be calculated and replaced
     */
    void                        modulo                      (std::vector<uint32_t> & num) const;
    /**
     * Cheks whether a long number equals to zero
     * @param val Number to be cheked
     * @return true if number is zero false otherwise
     */
    bool                        isZero                      (const std::vector<uint32_t> & val) const;
};

#endif //SEMESTRALKA_CBIGNUM_H
