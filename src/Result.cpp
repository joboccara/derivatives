#include "Result.hpp"

Result::Result(double value)
: m_value(value)
, m_dTarget_dMe()
, m_parameter()
{
    
}

void Result::computeDerivatives(Derivatives& derivatives, double dTarget_dMe)
{
    m_dTarget_dMe = dTarget_dMe;
    if (m_parameter != Parameter())
    {
       derivatives.addDerivative(m_parameter, m_dTarget_dMe);
    }
    compute_dTarget_dDependencies(derivatives, dTarget_dMe);
}

void Result::setAsParameter(const Parameter& parameter)
{
    m_parameter = parameter;
}

double Result::getValue() const
{
    return m_value;
}


