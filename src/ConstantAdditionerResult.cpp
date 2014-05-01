#include "ConstantAdditionerResult.hpp"

using namespace algo_diff;

ConstantAdditionerResult::ConstantAdditionerResult(boost::shared_ptr<Result> operand, double constant)
: Result(operand->getValue() + constant)
, m_operand(operand)
{
    
}

void ConstantAdditionerResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    m_operand->computeDerivatives(derivatives, dTarget_dMe);
}



