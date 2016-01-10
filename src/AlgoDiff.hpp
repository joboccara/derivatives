#include "Derivatives.hpp"
#include "GenericFunction.hpp"
#include "Parameter.hpp"
#include "Variable.hpp"

#include <cmath>
#include "MathFunctions.hpp"

/*  ************ LIBRARY DESCRIPTION *************

    This library implements reverse algorithmic differentiation which allows rapid
    numerical derivative calculation, optimal when few results are derived with 
    regards to few to many parameters. The library is very simple to use as its
    impact on existing code is minimal.



    ************ DERIVATIVE CALCULATION **********

    To compute derivatives, simply use algo_diff::Variable where double would be
    normally used in the function calculation code. Indicate parameters with regards
    to which the result should be derived (either when constructing the Variable
    like x in the example or later like y). Then retrieve the derivatives from the
    function result in a algo_diff::Derivatives instance.

    Utilisation example:

    using namespace algo_diff;
    Variable x(3., "x");
    x += 4;
    Variable y(-2.);
    y += 4;
    y.setAsParameter("y");
    Variable z = (2 / sin(y) + 3) / ((1 + x) * (1 - x));
    z *= 2 * x;

    Derivatives results;
    z.computeDerivatives(results);
    std::cout << "z = " << z.getValue() << std::endl;
    std::cout << "dz/dx = " << results.getDerivative("x") << std::endl;
    std::cout << "dy/dx = " << results.getDerivative("y") << std::endl;


    ************ USER DEFINED FUNCTIONS **********

    User-defined functions can be used in the calculation if they are declared with
    their derived function with the macro:
    DEFINE_DERIVED_FUNCTION(function, derivedFunction)
    See below for such declarations with a few standard functions.
    The functions and derived functions must have external linkage (not be declared
    static)
*/

DEFINE_DERIVED_FUNCTION(sin, cos)
DEFINE_DERIVED_FUNCTION(cos, minusSin)
DEFINE_DERIVED_FUNCTION(exp, exp)
DEFINE_DERIVED_FUNCTION(log, inverse)
DEFINE_DERIVED_FUNCTION(sqrt, sqrtDerivative)


