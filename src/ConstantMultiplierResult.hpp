#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

class ConstantMultiplierResult : public Result
{
public:
    ConstantMultiplierResult(boost::shared_ptr<Result> operand, double constant);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    const double m_constant;
    boost::shared_ptr<Result> const m_operand;
};


