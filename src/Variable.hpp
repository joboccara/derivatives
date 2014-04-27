#pragma once

#include "Result.hpp"

#include "boost/shared_ptr.hpp"

class Variable
{
public:
    explicit Variable(double value);
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
private:
    explicit Variable(boost::shared_ptr<Result> result);
    boost::shared_ptr<Result> m_result;
};

Variable operator+(const Variable& operand1, const Variable& operand2);
Variable operator+(const Variable& operand, double constant);
Variable operator+(double constant, const Variable& operand);
Variable operator-(const Variable& operand1, const Variable& operand2);
Variable operator-(const Variable& operand, double constant);
Variable operator-(double constant, const Variable& operand);
Variable operator*(const Variable& operand1, const Variable& operand2);
Variable operator*(const Variable& operand, double constant);
Variable operator*(double constant, const Variable& operand);
Variable operator/(const Variable& operand1, const Variable& operand2);
Variable operator/(const Variable& operand, double constant);
Variable operator/(double constant, const Variable& operand);


