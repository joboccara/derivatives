#include "ConstantResult.hpp"

using namespace algo_diff;

ConstantResult::ConstantResult(double value)
: Result(value)
{
    
}

void ConstantResult::compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe)
{
    
}


