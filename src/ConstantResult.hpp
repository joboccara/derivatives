#pragma once

#include "Result.hpp"

namespace algo_diff
{

class ConstantResult : public Result
{
public:
    explicit ConstantResult(double value);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);
};

} // namespace algo_diff

