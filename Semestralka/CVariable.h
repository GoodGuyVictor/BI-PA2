//
// Created by victor on 17.5.18.
//

#ifndef SEMESTRALKA_CVARIABLE_H
#define SEMESTRALKA_CVARIABLE_H

#include <string>

class CVariable
{
public:
    CVariable (const std::string &name, const std::string val)
            : m_name(name), m_value(val) {}

private:
    std::string m_name;
    std::string m_value;
};

#endif //SEMESTRALKA_CVARIABLE_H
