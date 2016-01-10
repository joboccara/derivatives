#include "Variable.hpp"

#include "ConstantResult.hpp"
#include "OneParameterResult.hpp"
#include "TwoParametersResult.hpp"

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

Variable::Variable(double value, const Parameter& parameter)
: m_result(new ConstantResult(value))
{
    setAsParameter(parameter);
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
    m_result = boost::shared_ptr<Result>(new TwoParametersResult(m_result, other.m_result,
                                                [](double a, double b){return a + b;},
                                                [](double, double){return 1.;},
                                                [](double, double){return 1.;}));
    return *this;
}

Variable& Variable::operator+=(double constant)
{
    m_result = boost::shared_ptr<Result>(new OneParameterResult(m_result,
                                                [constant](double a){return a + constant;},
                                                [](double){return 1.;}));
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
    m_result = boost::shared_ptr<Result>(new TwoParametersResult(m_result, other.m_result,
                                                [](double a, double b){return a - b;},
                                                [](double, double){return 1.;},
                                                [](double, double){return -1.;}));
    return *this;
}

Variable& Variable::operator-=(double constant)
{
    m_result = boost::shared_ptr<Result>(new OneParameterResult(m_result,
                                                [constant](double a){return a - constant;},
                                                [](double){return 1.;}));
    return *this;
}

Variable Variable::operator-() const
{
    return Variable(boost::shared_ptr<Result>(new OneParameterResult(m_result,
                                                     [](double a){return -a;},
                                                     [](double){return -1.;})));
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
    m_result = boost::shared_ptr<Result>(new TwoParametersResult(m_result, other.m_result,
                                                [](double a, double b){return a * b;},
                                                [](double, double b){return b;},
                                                [](double a, double){return a;}));
    return *this;
}

Variable& Variable::operator*=(double constant)
{
    m_result = boost::shared_ptr<Result>(new OneParameterResult(m_result,
                                                [constant](double a){return a * constant;},
                                                [constant](double){return constant;}));
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
    m_result = boost::shared_ptr<Result>(new TwoParametersResult(m_result, other.m_result,
                                                [](double a, double b){return a / b;},
                                                [](double, double b){return 1 / b;},
                                                [](double a, double b){return -a / (b * b);}));
    return *this;
}

Variable& Variable::operator/=(double constant)
{
    m_result = boost::shared_ptr<Result>(new OneParameterResult(m_result,
                                                [constant](double a){return a / constant;},
                                                [constant](double){return 1 / constant;}));
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

