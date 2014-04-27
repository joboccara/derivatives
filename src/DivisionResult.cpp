#include "DivisionResult.hpp"

DivisionResult::DivisionResult(boost::shared_ptr<Result> operand1, boost::shared_ptr<Result> operand2)
: Result(operand1->getValue() / operand2->getValue())
, m_operand1(operand1)
, m_operand2(operand2)
{
    
}

void DivisionResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    double operand1 = m_operand1->getValue();
    double operand2 = m_operand2->getValue();
    m_operand1->computeDerivatives(derivatives, 1 / operand2 * dTarget_dMe);
    m_operand2->computeDerivatives(derivatives, -operand1 / (operand2 * operand2) * dTarget_dMe);
}





