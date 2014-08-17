#include "AlgoDiff.hpp"

#include <cmath>
#include <vector>


using namespace algo_diff;
typedef int Date;

namespace
{
    
struct Dividend
{
    enum Nature
    {
        Absolute
       ,ForwardProportional
    };

    Dividend(const Date& aDate, double aValue, Nature aNature)
    : date(aDate), value(aValue), nature(aNature){ }

    Date date;
    double value;
    Nature nature;
};

const double SpotDefaultValue = 400.;
template<typename value_type>
struct Parameters
{
    Parameters(): spot(SpotDefaultValue), dividends(), rate(), spotDate(), maturity() { }
    value_type spot;
    std::vector<Dividend> dividends;
    double rate;
    Date spotDate;
    Date maturity;
};

template<typename value_type>
void initializeDefaultParameters(Parameters<value_type>& parameters)
{
    parameters.spot = value_type(SpotDefaultValue);
    parameters.rate = 0.03;
    parameters.spotDate = 0;
    parameters.maturity = 50 * 365;
    for (Date date = parameters.spotDate; date < parameters.maturity; date += 7)
    {
        parameters.dividends.push_back(Dividend(date, 0.01, Dividend::Absolute));
        parameters.dividends.push_back(Dividend(date, 0.1, Dividend::ForwardProportional));
    }
}

double getCapitalizationFactor(double rate, const Date& date1, const Date& date2)
{
    return exp(rate * (date2 - date1) / 365);
}

template<typename value_type>
class ForwardCalculator
{
public:
    static value_type compute(const Parameters<value_type>& parameters)
    {
        value_type forward(parameters.spot);
        Date currentDate = parameters.spotDate;
        for (std::vector<Dividend>::const_iterator it = parameters.dividends.begin(); it != parameters.dividends.end(); ++it)
        {
            const Dividend& dividend = *it;
            forward *= getCapitalizationFactor(parameters.rate, currentDate, dividend.date);
            forward -= computeDividend(dividend, forward);
            currentDate = dividend.date;
        }
        forward *= getCapitalizationFactor(parameters.rate, currentDate, parameters.maturity);
        return forward;
    }
private:
    static value_type computeDividend(const Dividend& dividend, const value_type& forward)
    {
        if (dividend.nature == Dividend::Absolute)
        {
            return value_type(dividend.value);
        }
        else if (dividend.nature == Dividend::ForwardProportional)
        {
            return dividend.value * forward / 100;
        }
    }
};

} // anonymous namepace

double compute_dfds_classic()
{
    Parameters<double> parameters;
    initializeDefaultParameters(parameters);
    double forward = ForwardCalculator<double>::compute(parameters);
    double dShift = 1.;
    parameters.spot += dShift;
    double shiftedForward = ForwardCalculator<double>::compute(parameters);
    return (shiftedForward - forward) / dShift;
}

double compute_dfds_algodiff()
{
    Parameters<Variable> parameters;
    initializeDefaultParameters(parameters);
    parameters.spot.setAsParameter("spot");
    Variable forward = ForwardCalculator<Variable>::compute(parameters);
    Derivatives results;
    forward.computeDerivatives(results);
    return results.getDerivative("spot");
}

