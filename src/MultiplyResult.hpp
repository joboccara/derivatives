#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

class MultiplyResult : public Result
{
public:
    MultiplyResult(boost::shared_ptr<Result> operand1, boost::shared_ptr<Result> operand2);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    boost::shared_ptr<Result> const m_operand1;
    boost::shared_ptr<Result> const m_operand2;
};


