#include "Derivatives.hpp"

using namespace algo_diff;

bool Derivatives::empty() const
{
    return derivatives.empty();
}

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

void Derivatives::addLocalDerivatives(const Derivatives& localDerivatives, double dTarget_dLocal)
{
    for (ValuesMap::const_iterator it = localDerivatives.derivatives.begin(); it != localDerivatives.derivatives.end(); ++it)
    {
        const ValuesMap::value_type& localDerivative = *it;
        const Parameter& parameter = localDerivative.first;
        double localDerivativeValue = localDerivative.second;
        derivatives[parameter] += dTarget_dLocal * localDerivativeValue;
    }
}


