#include "Derivatives.hpp"
#include "Variable.hpp"

#include <iostream>

void test1() // +, -
{
    Variable a(3.);
    a.setAsParameter(Parameter("a"));
    a += 2;
    a *= 4;
    Variable b(1.5);
    b.setAsParameter(Parameter("b"));
    Variable c = a - 3 * b;

    Derivatives results;
    c.computeDerivatives(results);
    std::cout << c.getValue() << std::endl;
    std::cout << results.getDerivative(Parameter("a")) << std::endl;
    std::cout << results.getDerivative(Parameter("b")) << std::endl;
}

void test2() // *
{
    Variable t(2.);
    t.setAsParameter("time");
    Variable r = (1 - t) * (2 + t * t);

    Derivatives results;
    r.computeDerivatives(results);
    std::cout << "value = " << r.getValue() << std::endl;
    std::cout << "derivative = " << results.getDerivative("time") << std::endl;
}

void test3() // /
{
    Variable x(3.);
    x.setAsParameter("Length");
    Variable z = (2 / x + 3) / ((1 + x) * (1 - x));

    Derivatives results;
    z.computeDerivatives(results);
    std::cout << "value = " << z.getValue() << std::endl;
    std::cout << "derivative = " << results.getDerivative("Length") << std::endl;
}

int main()
{
    test3();
    return 0;
}
