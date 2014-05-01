#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class MinusResult : public Result
{
public:
    MinusResult(boost::shared_ptr<Result> operand1, boost::shared_ptr<Result> operand2);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    const boost::shared_ptr<Result> m_operand1;
    const boost::shared_ptr<Result> m_operand2;
};

} // namespace algo_diff

