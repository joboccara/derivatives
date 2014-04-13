#include <iostream>
#include <vector>

struct VariableType
{
    enum Type
    {
        None
       ,Spot
       ,Dividend
    };
};

struct Derivatives
{
    Derivatives(int iNbDividends);
    double dValue_dSpot;
    std::vector<double> dValue_dDividends;
};

Derivatives::Derivatives(int iNbDividends)
: dValue_dSpot()
, dValue_dDividends(iNbDividends)
{
    
}

class Result
{
public:
    explicit Result(double value);
    virtual ~Result(){ };

    void computeDerivatives(Derivatives&, double dTarget_dMe);
    void setAsSpot();
    void setAsDividend(int iDividend);

    double getValue() const;
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe) = 0; // template method design pattern
    Result(const Result&);
    Result& operator=(const Result&);

    double m_value;
    double m_dTarget_dMe;
    VariableType::Type m_variableType;
    int m_iDividend;
};

Result::Result(double value)
: m_value(value)
, m_dTarget_dMe()
, m_variableType(VariableType::None)
, m_iDividend()
{
    
}

void Result::computeDerivatives(Derivatives& derivatives, double dTarget_dMe)
{
    m_dTarget_dMe = dTarget_dMe;
    if (m_variableType == VariableType::Spot)
    {
        derivatives.dValue_dSpot += dTarget_dMe;
    }
    {
        derivatives.dValue_dDividends[m_iDividend] += dTarget_dMe;
    }
    compute_dTarget_dDependencies(derivatives, dTarget_dMe);
}

void Result::setAsSpot()
{
    m_variableType = VariableType::Spot;
}

void Result::setAsDividend(int iDividend)
{
    m_variableType = VariableType::Dividend;
    m_iDividend = iDividend;
}

double Result::getValue() const
{
    return m_value;
}

class PlusResult : public Result
{
public:
    PlusResult(Result* operand1, Result* operand2);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    Result* const m_operand1;
    Result* const m_operand2;
};

PlusResult::PlusResult(Result* operand1, Result* operand2)
: Result(operand1->getValue() + operand2->getValue())
, m_operand1(operand1)
, m_operand2(operand2)
{
    
}

void PlusResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    m_operand1->computeDerivatives(derivatives, dTarget_dMe);
    m_operand2->computeDerivatives(derivatives, dTarget_dMe);
}

class ConstantMultiplierResult : public Result
{
public:
    ConstantMultiplierResult(Result* operand, double constant);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);

    const double m_constant;
    Result* const m_operand;
};

ConstantMultiplierResult::ConstantMultiplierResult(Result* operand, double constant)
: Result(constant * operand->getValue())
, m_constant(constant)
, m_operand(operand)
{
    
}

void ConstantMultiplierResult::compute_dTarget_dDependencies(Derivatives& derivatives, double dTarget_dMe)
{
    m_operand->computeDerivatives(derivatives, m_constant * dTarget_dMe);
}

class ConstantResult : public Result
{
public:
    explicit ConstantResult(double value);
private:
    virtual void compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe);
};

ConstantResult::ConstantResult(double value)
: Result(value)
{
    
}

void ConstantResult::compute_dTarget_dDependencies(Derivatives&, double dTarget_dMe)
{
    
}

class Variable
{
public:
    Variable(double value);
    Variable& operator+=(const Variable& other);
    Variable& operator*=(double constant);
    
    void setAsSpot();
    void setAsDividend(int iDividend);
    void computeDerivatives(Derivatives&, double dTarget_dMe = 1);
private:
    Variable(Result* result);
    Result* m_result;
};

Variable::Variable(Result* result)
: m_result(result)
{
    
}

Variable::Variable(double value)
: m_result(new ConstantResult(value))
{
    
}

Variable& Variable::operator+=(const Variable& other)
{
    m_result = new PlusResult(m_result, other.m_result);
    return *this;
}

Variable operator+(const Variable& operand1, const Variable& operand2)
{
    return Variable(operand1) += operand2;
}

Variable& Variable::operator*=(double constant)
{
    m_result = new ConstantMultiplierResult(m_result, constant);
    return *this;
}

Variable operator*(const Variable& operand, double constant)
{
    return Variable(operand) *= constant;
}

Variable operator*(double constant, const Variable& operand)
{
    return Variable(operand) *= constant;
}

void Variable::setAsSpot()
{
    m_result->setAsSpot();
}

void Variable::setAsDividend(int iDividend)
{
    m_result->setAsDividend(iDividend);
}

void Variable::computeDerivatives(Derivatives& derivatives, double dTarget_dMe)
{
    m_result->computeDerivatives(derivatives, dTarget_dMe);
}

int main()
{
    Variable a(3.);
    a.setAsSpot();
    a += 2;
    a *= 4;
    Derivatives results(0);
    a.computeDerivatives(results);

    std::cout << results.dValue_dSpot << std::endl;
    return 0;
}
