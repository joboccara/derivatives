#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class PlusResult : public Result
{
public:
    PlusResult(boost::shared_ptr<Result> operand1, boost::shared_ptr<Result> operand2);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    boost::shared_ptr<Result> const m_operand1;
    boost::shared_ptr<Result> const m_operand2;
};
} // namespace algo_diff

