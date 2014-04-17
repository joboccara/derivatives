#pragma once

#include "Result.hpp"

class PlusResult : public Result
{
public:
    PlusResult(Result* operand1, Result* operand2);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    Result* const m_operand1;
    Result* const m_operand2;
};

