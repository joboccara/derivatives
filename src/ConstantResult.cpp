#include "ConstantResult.hpp"

ConstantResult::ConstantResult(double value)
: Result(value)
{
    
}

void ConstantResult::compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe)
{
    
}


