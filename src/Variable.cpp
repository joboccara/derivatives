#include "Variable.hpp"

#include "ConstantMultiplierResult.hpp"
#include "ConstantResult.hpp"
#include "PlusResult.hpp"

Variable::Variable(Result* result)
: m_result(result)
{
    
}

Variable::Variable(double value)
: m_result(new ConstantResult(value))
{
    
}

Variable& Variable::operator+=(const Variable& other)
{
    m_result = new PlusResult(m_result, other.m_result);
    return *this;
}

Variable operator+(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) += operand2;
}

Variable& Variable::operator+=(double constant)
{
    return *this += Variable(constant);
}

Variable Variable::operator-() const
{
    return Variable(new ConstantMultiplierResult(m_result, -1.));
}

Variable operator-(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) += (-operand2);
}

Variable& Variable::operator*=(double constant)
{
    m_result = new ConstantMultiplierResult(m_result, constant);
    return *this;
}

Variable operator*(const Variable& operand, double constant)
{
    return Variable(operand) *= constant;
}

Variable operator*(double constant, const Variable& operand)
{
    return Variable(operand) *= constant;
}

void Variable::setAsParameter(const Parameter& parameter)
{
    m_result->setAsParameter(parameter);
}

double Variable::getValue() const
{
    return m_result->getValue();
}

void Variable::computeDerivatives(Derivatives& derivatives, double dTarget_dMe)
{
    m_result->computeDerivatives(derivatives, dTarget_dMe);
}


