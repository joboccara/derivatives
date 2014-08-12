#pragma once

#include "Result.hpp"
#include "Variable.hpp"

#include "boost/shared_ptr.hpp"

namespace algo_diff
{

template
<
    double (*function) (double),
    double (*derivedFunction)(double)
>
class GenericFunctionResult : public Result
{
public:
    GenericFunctionResult(boost::shared_ptr<Result> operand)
    : Result(function(operand->getValue()))
    , m_operand(operand)
    {
        
    }
private:
    virtual void compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
    {
        m_operand->computeDerivatives(derivatives, derivedFunction(m_operand->getValue()) * dTarget_dMe);
    }

    boost::shared_ptr<Result> const m_operand;
};

} // namespace algo_diff

#define DEFINE_DERIVED_FUNCTION(function, derivedFunction) \
inline algo_diff::Variable function(const algo_diff::Variable& operand) \
{ \
    using namespace algo_diff; \
    return Variable(boost::shared_ptr<Result>(new GenericFunctionResult<function, derivedFunction>(operand.m_result))); \
}

