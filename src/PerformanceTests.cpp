#include "AlgoDiff.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>


using namespace algo_diff;
using namespace std;
typedef int Date;

namespace
{
    
template<typename value_type>
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
    value_type value;
    Nature nature;
};

const double SpotDefaultValue = 400.;
template<typename value_type>
struct Parameters
{
    Parameters(): spot(SpotDefaultValue), dividends(), rate(), spotDate(), maturity() { }
    value_type spot;
    vector<Dividend<value_type> > dividends;
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
        parameters.dividends.push_back(Dividend<value_type>(date, 0.01, Dividend<value_type>::Absolute));
        parameters.dividends.push_back(Dividend<value_type>(date, 0.1, Dividend<value_type>::ForwardProportional));
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
        for (typename vector<Dividend<value_type> >::const_iterator it = parameters.dividends.begin(); it != parameters.dividends.end(); ++it)
        {
            const Dividend<value_type>& dividend = *it;
            forward *= getCapitalizationFactor(parameters.rate, currentDate, dividend.date);
            forward -= computeDividend(dividend, forward);
            currentDate = dividend.date;
        }
        forward *= getCapitalizationFactor(parameters.rate, currentDate, parameters.maturity);
        return forward;
    }
private:
    static value_type computeDividend(const Dividend<value_type>& dividend, const value_type& forward)
    {
        if (dividend.nature == Dividend<value_type>::Absolute)
        {
            return dividend.value;
        }
        else if (dividend.nature == Dividend<value_type>::ForwardProportional)
        {
            return dividend.value * forward / 100;
        }
    }
};

static double compute_one_derivative_classic(double& parameterToShift, double dShift, const Parameters<double>& parameters, double forward)
{
}

vector<double> compute_forward_derivatives_classic(size_t nbDividendsDerivatives)
{
    Parameters<double> parameters;
    initializeDefaultParameters(parameters);
    double forward = ForwardCalculator<double>::compute(parameters);
    vector<double> results;
    for (int i = 0; i < nbDividendsDerivatives; ++i)
    {
        if (i < parameters.dividends.size())
        {
            double dShift = 0.2;
            parameters.dividends[i].value += dShift;
            double shiftedForward = ForwardCalculator<double>::compute(parameters);
            double dFdDiv = (shiftedForward - forward) / dShift;
            parameters.dividends[i].value -= dShift;
            results.push_back(dFdDiv);
        }
    }
    return results;
}

string getDividendId(int iDividend)
{
    ostringstream dividendId;
    dividendId << "dividend" << iDividend;
    return dividendId.str();
}

vector<double> compute_forward_derivatives_algodiff(size_t nbDividendsDerivatives)
{
    Parameters<Variable> parameters;
    initializeDefaultParameters(parameters);
    size_t nbComputedDerivatives = min(nbDividendsDerivatives, parameters.dividends.size());
    for (int i = 0; i < nbComputedDerivatives; ++i)
    {
        parameters.dividends[i].value.setAsParameter(getDividendId(i));
    }
    Variable forward = ForwardCalculator<Variable>::compute(parameters);
    Derivatives derivatives;
    forward.computeDerivatives(derivatives);

    vector<double> results;
    for (int i = 0; i < nbComputedDerivatives; ++i)
    {
        double dFdDiv = derivatives.getDerivative(getDividendId(i));
        results.push_back(dFdDiv);
    }
    return results;
}

template<typename Container>
void printContainer(const Container& c, string title)
{
    cout << "CONTENTS OF: " << title << endl;
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}

} // anonymous namepace

void launchPerformanceTests(size_t nbDerivatives)
{
    printContainer(compute_forward_derivatives_classic(nbDerivatives), "classic results");
    printContainer(compute_forward_derivatives_algodiff(nbDerivatives), "algodiff results");
}

