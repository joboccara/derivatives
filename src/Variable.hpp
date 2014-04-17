#pragma once

#include "Result.hpp"

class Variable
{
public:
    explicit Variable(double value);
    Variable& operator+=(const Variable& other);
    Variable& operator+=(double constant);
    Variable& operator*=(double constant);
    Variable operator-() const;
    
    void setAsParameter(const Parameter&);
    void computeDerivatives(Derivatives&, double dTarget_dMe = 1);

    double getValue() const;
private:
    Variable(Result* result);
    Result* m_result;
};

Variable operator+(const Variable& operand1, const Variable& operand2);
Variable operator-(const Variable& operand1, const Variable& operand2);
Variable operator*(const Variable& operand, double constant);
Variable operator*(double constant, const Variable& operand);


