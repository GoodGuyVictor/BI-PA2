#include "COperand.h"

class CLongInteger : public COperand
{
private:
    vector<int> m_value;
public:
    explicit CLongInteger(const string & val) : COperand(val, VAL_LONGINT) {};

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