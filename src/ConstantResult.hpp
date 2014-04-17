#pragma once

#include "Result.hpp"

class ConstantResult : public Result
{
public:
    explicit ConstantResult(double value);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);
};


