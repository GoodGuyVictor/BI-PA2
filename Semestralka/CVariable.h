#include "COperand.h"
#include <string>

using namespace std;

class CVariable : public COperand
{
private:
    string m_name;
public:
    explicit CVariable(const string & name, const string & val, EValType type)
            : COperand(val, type), m_name(name) {};

    COperand * addInteger               (const COperand & other) override;
    COperand * addLongInteger           (const COperand & other) override;
    COperand * addDecimal               (const COperand & other) override;

    COperand * subtractInteger          (const COperand & other) override;
    COperand * subtractLongInteger      (const COperand & other) override;
    COperand * subtractDecimal          (const COperand & other) override;

    COperand * multiplyByInteger        (const COperand & other) override;
    COperand * multiplyByLongInteger    (const COperand & other) override;
    COperand * multiplyByDecimal        (const COperand & other) override;

    COperand * devideByInteger          (const COperand & other) override;
    COperand * devideByLongInteger      (const COperand & other) override;
    COperand * devideByDecimal          (const COperand & other) override;
};