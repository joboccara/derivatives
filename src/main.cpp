#include "AlgoDiff.hpp"

#include <iostream>

void test1() // +, -
{
    algo_diff::Variable a(3.);
    a.setAsParameter(algo_diff::Parameter("a"));
    a += 2;
    a *= 4;
    algo_diff::Variable b(1.5);
    b.setAsParameter(algo_diff::Parameter("b"));
    algo_diff::Variable c = a - 3 * b;

    algo_diff::Derivatives results;
    c.computeDerivatives(results);
    std::cout << c.getValue() << std::endl;
    std::cout << results.getDerivative(algo_diff::Parameter("a")) << std::endl;
    std::cout << results.getDerivative(algo_diff::Parameter("b")) << std::endl;
}

void test2() // *
{
    using namespace algo_diff;
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
    using namespace algo_diff;
    Variable x(3.);
    x.setAsParameter("x");
    Variable z = (2 / x + 3) / ((1 + x) * (1 - x));

    Derivatives results;
    z.computeDerivatives(results);
    std::cout << "value = " << z.getValue() << std::endl;
    std::cout << "derivative = " << results.getDerivative("Length") << std::endl;
}

void test4() // user defined functions
{
    using namespace algo_diff;
    Variable x(3.141592657 / 4);
    x.setAsParameter("x");
    Variable s = 2 * sin(x);

    Derivatives results;
    s.computeDerivatives(results);
    std::cout << "value = " << s.getValue() << std::endl;
    std::cout << "derivative = " << results.getDerivative("x") << std::endl;
}

void test5() // doc example
{
    using namespace algo_diff;
    Variable x(3.);
    x.setAsParameter("x");
    x += 4;
    Variable y(-2.);
    y.setAsParameter("y");
    x += 4;
    Variable z = (2 / sin(y) + 3) / ((1 + x) * (1 - x));
    z *= 2 * x;

    Derivatives results;
    z.computeDerivatives(results);
    std::cout << "z = " << z.getValue() << std::endl;
    std::cout << "dz/dx = " << results.getDerivative("x") << std::endl;
    std::cout << "dy/dx = " << results.getDerivative("y") << std::endl;
}

int main()
{
    test5();
    return 0;
}
