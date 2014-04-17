#include "PlusResult.hpp"

PlusResult::PlusResult(Result* operand1, Result* operand2)
: Result(operand1->getValue() + operand2->getValue())
, m_operand1(operand1)
, m_operand2(operand2)
{
    
}

void PlusResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    m_operand1->computeDerivatives(derivatives, dTarget_dMe);
    m_operand2->computeDerivatives(derivatives, dTarget_dMe);
}



