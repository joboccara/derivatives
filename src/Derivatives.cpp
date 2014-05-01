#include "Derivatives.hpp"

using namespace algo_diff;

double Derivatives::getDerivative(const Parameter& parameter) const
{
    ValuesMap::const_iterator lb = derivatives.lower_bound(parameter);
    if (lb != derivatives.end() && !derivatives.key_comp()(parameter, lb->first)) // if there is an equivalent object to parameter in the map
    {
        return lb->second;
    }
    else
    {
        return 0.;
    }
}

void Derivatives::addDerivative(const Parameter& parameter, double value)
{
    derivatives[parameter] += value;
}


