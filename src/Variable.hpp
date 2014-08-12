#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

namespace algo_diff
{

class Variable
{
public:
    explicit Variable(double value);
    Variable(double value, const Parameter&);
    Variable& operator+=(const Variable& other);
    Variable& operator+=(double constant);
    Variable& operator-=(const Variable& other);
    Variable& operator-=(double constant);
    Variable operator-() const;
    Variable& operator*=(const Variable& other);
    Variable& operator*=(double constant);
    Variable& operator/=(const Variable& other);
    Variable& operator/=(double constant);
    
    void setAsParameter(const Parameter&);
    void computeDerivatives(Derivatives&, double dTarget_dMe = 1);

    double getValue() const;

//private:
    explicit Variable(boost::shared_ptr<Result> result);
    boost::shared_ptr<Result> m_result;
};

} // namespace algo_diff

algo_diff::Variable operator+(const algo_diff::Variable& operand1, const algo_diff::Variable& operand2);
algo_diff::Variable operator+(const algo_diff::Variable& operand, double constant);
algo_diff::Variable operator+(double constant, const algo_diff::Variable& operand);
algo_diff::Variable operator-(const algo_diff::Variable& operand1, const algo_diff::Variable& operand2);
algo_diff::Variable operator-(const algo_diff::Variable& operand, double constant);
algo_diff::Variable operator-(double constant, const algo_diff::Variable& operand);
algo_diff::Variable operator*(const algo_diff::Variable& operand1, const algo_diff::Variable& operand2);
algo_diff::Variable operator*(const algo_diff::Variable& operand, double constant);
algo_diff::Variable operator*(double constant, const algo_diff::Variable& operand);
algo_diff::Variable operator/(const algo_diff::Variable& operand1, const algo_diff::Variable& operand2);
algo_diff::Variable operator/(const algo_diff::Variable& operand, double constant);
algo_diff::Variable operator/(double constant, const algo_diff::Variable& operand);


