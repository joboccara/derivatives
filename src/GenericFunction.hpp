#pragma once

#include "Result.hpp"
#include "OneParameterResult.hpp"
#include "Variable.hpp"

#include "boost/shared_ptr.hpp"

#define DEFINE_DERIVED_FUNCTION(function, derivedFunction) \
inline algo_diff::Variable function(const algo_diff::Variable& operand) \
{ \
    using namespace algo_diff; \
    return Variable(boost::shared_ptr<Result>(new OneParameterResult(operand.m_result, static_cast<double(&)(double)>(function), static_cast<double(&)(double)>(derivedFunction)))); \
}

