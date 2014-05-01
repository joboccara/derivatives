#include "Variable.hpp"

#include "ConstantAdditionerResult.hpp"
#include "ConstantMultiplierResult.hpp"
#include "ConstantResult.hpp"
#include "DivisionResult.hpp"
#include "MinusResult.hpp"
#include "MultiplyResult.hpp"
#include "PlusResult.hpp"

#include "boost/shared_ptr.hpp"

using namespace algo_diff;
    
Variable::Variable(boost::shared_ptr<Result> result)
: m_result(result)
{
    
}

Variable::Variable(double value)
: m_result(new ConstantResult(value))
{
    
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

// Addition

Variable& Variable::operator+=(const Variable& other)
{
    m_result = boost::shared_ptr<Result>(new PlusResult(m_result, other.m_result));
    return *this;
}

Variable& Variable::operator+=(double constant)
{
    m_result = boost::shared_ptr<Result>(new ConstantAdditionerResult(m_result, constant));
    return *this;
}

Variable operator+(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) += operand2;
}

Variable operator+(const Variable& operand, double constant)
{
    return Variable(operand) += constant;
}

Variable operator+(double constant, const Variable& operand)
{
    return Variable(operand) += constant;
}

// Subtraction

Variable& Variable::operator-=(const Variable& other)
{
    m_result = boost::shared_ptr<Result>(new MinusResult(m_result, other.m_result));
    return *this;
}

Variable& Variable::operator-=(double constant)
{
    m_result = boost::shared_ptr<Result>(new ConstantAdditionerResult(m_result, -constant));
    return *this;
}

Variable Variable::operator-() const
{
    return Variable(boost::shared_ptr<Result>(new ConstantMultiplierResult(m_result, -1.)));
}

Variable operator-(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) -= operand2;
}

Variable operator-(const Variable& operand, double constant)
{
    return Variable(operand) -= constant;
}

Variable operator-(double constant, const Variable& operand)
{
    return constant + (-operand);
}

//Multiplication

Variable& Variable::operator*=(const Variable& other)
{
    m_result = boost::shared_ptr<Result>(new MultiplyResult(m_result, other.m_result));
    return *this;
}

Variable& Variable::operator*=(double constant)
{
    m_result = boost::shared_ptr<Result>(new ConstantMultiplierResult(m_result, constant));
    return *this;
}

Variable operator*(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) *= operand2;
}

Variable operator*(const Variable& operand, double constant)
{
    return Variable(operand) *= constant;
}

Variable operator*(double constant, const Variable& operand)
{
    return Variable(operand) *= constant;
}

//Division

Variable& Variable::operator/=(const Variable& other)
{
    m_result = boost::shared_ptr<Result>(new DivisionResult(m_result, other.m_result));
    return *this;
}

Variable& Variable::operator/=(double constant)
{
    m_result = boost::shared_ptr<Result>(new ConstantMultiplierResult(m_result, 1 / constant));
    return *this;
}

Variable operator/(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) /= operand2;
}

Variable operator/(const Variable& operand, double constant)
{
    return Variable(operand) /= constant;
}

Variable operator/(double constant, const Variable& operand)
{
    return Variable(constant) / operand;
}

