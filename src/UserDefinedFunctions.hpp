#include "GenericFunctionResult.hpp"


/* You can associate functions with their derived functions below, using the macro
DEFINE_DERIVED_FUNCTION(function, derivedFunction)
The functions and derived functions must have external linkage (not be declared
static)
*/

#include <cmath>
#include "Math.hpp"

DEFINE_DERIVED_FUNCTION(sin, cos)
DEFINE_DERIVED_FUNCTION(cos, minusSin)
DEFINE_DERIVED_FUNCTION(exp, exp)
DEFINE_DERIVED_FUNCTION(log, inverse)
DEFINE_DERIVED_FUNCTION(sqrt, sqrtDerivative)


