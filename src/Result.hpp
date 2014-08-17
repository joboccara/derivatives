#pragma once

#include "Derivatives.hpp"
#include "Parameter.hpp"

#include "MemoryLogger.hpp"

namespace algo_diff
{

class Result //: public MemoryLogger<Result>
{
public:
    explicit Result(double value);
    virtual ~Result(){ };

    void computeDerivatives(Derivatives&, double dTarget_dMe);
    void setAsParameter(const Parameter&);

    double getValue() const;
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe) = 0; // template method design pattern
    Result(const Result&);
    Result& operator=(const Result&);

    double m_value;
    Parameter m_parameter;
    Derivatives m_localDerivatives;
};

} // namespace algo_diff

