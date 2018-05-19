//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CBIGNUM_H
#define SEMESTRALKA_CBIGNUM_H

class CBigNum
{
public:
    CBigNum(const int val)
    {
        m_sgn = val < 0;
        m_value.push_back((uint32_t)val);
    }

private:
    std::vector<uint32_t> m_value;
    bool m_sgn;
};

#endif //SEMESTRALKA_CBIGNUM_H
