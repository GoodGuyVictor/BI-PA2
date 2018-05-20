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
        m_fraction.push_back(fraction);
    }

    CBigNum(bool sgn, const std::vector<uint32_t > & val)
    {
        m_sgn = sgn;
        m_exponent = val;
    }

    CBigNum & operator+ (const CBigNum & other)
    {
        return *this;
    }

private:
    std::vector<uint32_t> m_exponent;
    std::vector<uint32_t> m_fraction;
    bool m_sgn;
};

#endif //SEMESTRALKA_CBIGNUM_H
