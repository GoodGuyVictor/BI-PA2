#include "CLongInteger.h"

CLongInteger::CLongInteger(std::string value)
{
    if(value[0] == '-') {
        m_sgn = true;
        value.erase(0,1);
    } else
        m_sgn = false;
    m_value = toBigInt(value);
}

std::vector<uint32_t> CLongInteger::toBigInt(std::string & value)
{
    std::vector<uint32_t> result;
    int len = value.size();
    int portions = len / 9;
    std::stringstream ss;
    uint32_t tmp;

    for(int i = 0; i < portions; i++) {
        ss << value.substr(value.size() - 9, 9);
        ss >> tmp;
        result.push_back(tmp);
        value.erase(value.size() - 9, 9);
        ss.clear();
    }

    if(!value.empty()) {
        ss << value;
        ss >> tmp;
        result.push_back(tmp);
    }

    return result;
}

CBigNum CLongInteger::evaluate() const
{
    return CBigNum(m_sgn, m_value);
}
