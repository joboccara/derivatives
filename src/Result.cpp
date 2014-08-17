#include "Result.hpp"

using namespace algo_diff;

Result::Result(double value)
: m_value(value)
, m_parameter()
, m_localDerivatives()
{
    
}

void Result::computeDerivatives(Derivatives& derivatives, double dTarget_dMe)
{
    if (m_localDerivatives.empty())
    {
        if (m_parameter != Parameter())
        {
            m_localDerivatives.addDerivative(m_parameter, 1);
        }
        compute_dTarget_dDependencies(m_localDerivatives, 1);
    }
    derivatives.addLocalDerivatives(m_localDerivatives, dTarget_dMe);
}

void Result::setAsParameter(const Parameter& parameter)
{
    m_parameter = parameter;
}

double Result::getValue() const
{
    return m_value;
}


