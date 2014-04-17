#pragma once

#include "Result.hpp"

class ConstantMultiplierResult : public Result
{
public:
    ConstantMultiplierResult(Result* operand, double constant);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    const double m_constant;
    Result* const m_operand;
};


