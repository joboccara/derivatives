#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class ConstantAdditionerResult : public Result
{
public:
    ConstantAdditionerResult(boost::shared_ptr<Result> operand, double constant);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    const boost::shared_ptr<Result> m_operand;
};


} // namespace algo_diff

