#pragma once

#include "Result.hpp"

#include <functional>
#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class TwoParametersResult : public Result
{
public:
    TwoParametersResult(boost::shared_ptr<Result> operand1, boost::shared_ptr<Result> operand2,
                        std::function<double(double,double)> f, std::function<double(double,double)> dfda, std::function<double(double,double)> dfdb)
    : Result(f(operand1->getValue(), operand2->getValue()))
    , m_operand1(operand1)
    , m_operand2(operand2)
    , m_dfda(dfda)
    , m_dfdb(dfdb)
    {
    }

private:
    virtual void compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
    {
        m_operand1->computeDerivatives(derivatives, dTarget_dMe * m_dfda(m_operand1->getValue(), m_operand2->getValue()));
        m_operand2->computeDerivatives(derivatives, dTarget_dMe * m_dfdb(m_operand1->getValue(), m_operand2->getValue()));
    }

private:
    boost::shared_ptr<Result> const m_operand1;
    boost::shared_ptr<Result> const m_operand2;
    std::function<double(double,double)> m_dfda;
    std::function<double(double,double)> m_dfdb;
};

}

