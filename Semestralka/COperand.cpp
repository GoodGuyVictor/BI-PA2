#include "COperand.h"

COperand *COperand::operator+(const COperand &other)
{
    switch(other.m_type)
    {
        case VAL_INT:       return addInteger(other);
        case VAL_LONGINT:   return addLongInteger(other);
        case VAL_DEC:       return addDecimal(other);
    }
}

COperand *COperand::operator-(const COperand &other)
{
    switch(other.m_type)
    {
        case VAL_INT:       return subtractInteger(other);
        case VAL_LONGINT:   return subtractLongInteger(other);
        case VAL_DEC:       return subtractDecimal(other);
    }
}

COperand *COperand::operator*(const COperand &other)
{
    switch(other.m_type)
    {
        case VAL_INT:       return multiplyByInteger(other);
        case VAL_LONGINT:   return multiplyByLongInteger(other);
        case VAL_DEC:       return multiplyByDecimal(other);
    }
}

COperand *COperand::operator/(const COperand &other)
{
    switch(other.m_type)
    {
        case VAL_INT:       return devideByInteger(other);
        case VAL_LONGINT:   return devideByLongInteger(other);
        case VAL_DEC:       return devideByDecimal(other);
    }
}

//COperand *COperand::operator%(const COperand &other)
//{
//    switch(other.m_type)
//    {
//        case VAL_INT:       return subtractInteger(other);
//        case VAL_LONGINT:   return subtractLongInteger(other);
//        case VAL_DEC:       return subtractDecimal(other);
//    }
//}