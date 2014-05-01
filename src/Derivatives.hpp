#pragma once

#include "Parameter.hpp"

#include <map>

namespace algo_diff
{

class Derivatives
{
public:
    double getDerivative(const Parameter&) const;
    void addDerivative(const Parameter&, double value);
private:
    typedef std::map<Parameter, double> ValuesMap;
    ValuesMap derivatives;
};

} // namespace algo_diff

