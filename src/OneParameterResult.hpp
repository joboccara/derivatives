#pragma once

#include "Result.hpp"

#include <functional>
#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class OneParameterResult : public Result
{
public:
    OneParameterResult(boost::shared_ptr<Result> operand, std::function<double(double)> f, std::function<double(double)> dfda)
    : Result(f(operand->getValue()))
    , m_operand(operand)
    , m_dfda(dfda)
    {
        
    }
private:
    virtual void compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
    {
        m_operand->computeDerivatives(derivatives, dTarget_dMe * m_dfda(m_operand->getValue()));
    }
private:
    boost::shared_ptr<Result> const m_operand;
    std::function<double(double)> m_dfda;
};

}
