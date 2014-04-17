#include "ConstantMultiplierResult.hpp"

ConstantMultiplierResult::ConstantMultiplierResult(Result* operand, double constant)
: Result(constant * operand->getValue())
, m_constant(constant)
, m_operand(operand)
{
    
}

void ConstantMultiplierResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    m_operand->computeDerivatives(derivatives, m_constant * dTarget_dMe);
}


