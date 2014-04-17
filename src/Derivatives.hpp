#pragma once

#include "Parameter.hpp"

#include <map>

class Derivatives
{
public:
    double getDerivative(const Parameter&) const;
    void addDerivative(const Parameter&, double value);
private:
    typedef std::map<Parameter, double> ValuesMap;
    ValuesMap derivatives;
};


