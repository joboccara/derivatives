#pragma once

#include "Parameter.hpp"

#include <map>

namespace algo_diff
{

class Derivatives
{
public:
    bool empty() const;
    double getDerivative(const Parameter&) const;
    void addDerivative(const Parameter&, double value);
    void addLocalDerivatives(const Derivatives& localDerivatives, double dTarget_dLocal);
private:
    typedef std::map<Parameter, double> ValuesMap;
    ValuesMap derivatives;
};

} // namespace algo_diff

