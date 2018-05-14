#include <string>

using namespace std;

class InvalidInput{};

enum EValType { VAL_INT, VAL_LONGINT, VAL_DEC };


class COperand
{
protected:
    string m_value;
    EValType m_type;

public:
                COperand                (const string & val, EValType type)
            : m_value(val), m_type(type) {};
    virtual    ~COperand                 () = default;

    COperand * operator +               (const COperand & other);
    COperand * operator -               (const COperand & other);
    COperand * operator *               (const COperand & other);
    COperand * operator /               (const COperand & other);
    COperand * operator %               (const COperand & other);

    virtual void       evaluate                 (const COperand & other) const = 0;

    virtual COperand * addInteger               (const COperand & other) = 0;
    virtual COperand * addLongInteger           (const COperand & other) = 0;
    virtual COperand * addDecimal               (const COperand & other) = 0;

    virtual COperand * subtractInteger          (const COperand & other) = 0;
    virtual COperand * subtractLongInteger      (const COperand & other) = 0;
    virtual COperand * subtractDecimal          (const COperand & other) = 0;

    virtual COperand * multiplyByInteger        (const COperand & other) = 0;
    virtual COperand * multiplyByLongInteger    (const COperand & other) = 0;
    virtual COperand * multiplyByDecimal        (const COperand & other) = 0;

    virtual COperand * devideByInteger          (const COperand & other) = 0;
    virtual COperand * devideByLongInteger      (const COperand & other) = 0;
    virtual COperand * devideByDecimal          (const COperand & other) = 0;
};