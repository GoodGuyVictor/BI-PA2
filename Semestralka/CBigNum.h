//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBIGNUM_H
#define SEMESTRALKA_CBIGNUM_H

#include <sstream>

class CBigNum
{
public:
    CBigNum() = default;

    CBigNum(int val)
    {
        if(val < 0) {
            m_sgn = true;
            val *= -1;
        } else
            m_sgn = false;
        m_exponent.push_back((uint32_t)val);
    }

    CBigNum(double val)
    {
        if(val < 0) {
            m_sgn = true;
            val *= -1;
        } else
            m_sgn = false;

        std::string dStr = std::to_string(val);

        char * token;
        token = strtok((char*)dStr.c_str(), ".");
        std::stringstream ss;
        ss << token;
        uint32_t exponent;
        ss >> exponent;
        m_exponent.push_back(exponent);
        ss.clear();

        token = strtok(NULL, ".");
        ss << token;
        uint32_t fraction;
        ss >> fraction;
        m_fraction = fraction;
    }

    CBigNum(bool sgn, const std::vector<uint32_t > & val)
    {
        m_sgn = sgn;
        m_exponent = val;
    }

    CBigNum & operator+ (const CBigNum & other)
    {

        if(m_sgn == true && other.m_sgn == false || m_sgn == false && other.m_sgn == true)
            return operator-(other);

        std::vector<uint32_t> exponent1 = m_exponent;
        std::vector<uint32_t> exponent2 = other.m_exponent;

        //if lengths are different expand the shorter one with zeros
        size_t n;
        if(exponent1.size() == exponent2.size())
            n = exponent1.size();
        else if(exponent1.size() > exponent2.size()) {
            n = exponent2.size();
            for(size_t i = n; i < exponent1.size(); i++)
                exponent2.push_back(0);
        }
        else {
            n = exponent1.size();
            for(size_t i = n; i < exponent2.size(); i++)
                exponent1.push_back(0);
        }


        std::vector<uint32_t> result;
        uint64_t tmp;
        unsigned short carry = 0;
        for(size_t i = 0; i < exponent1.size(); i++) {
            tmp = (uint64_t)m_exponent[i] + (uint64_t)other.m_exponent[i] + carry;
            result.push_back((uint32_t)tmp);
            carry = tmp >> 32;
        }

        if(carry)
            result.push_back(carry);

        m_exponent = result;
        return *this;
    }

    CBigNum &operator- (const CBigNum & other)
    {

    }

private:
    std::vector<uint32_t> m_exponent;
    uint32_t m_fraction;
    bool m_sgn;
};

#endif //SEMESTRALKA_CBIGNUM_H
