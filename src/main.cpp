#include "Derivatives.hpp"
#include "Variable.hpp"

#include "Result.hpp"
#include "MemoryLogger.hpp"

#include <iostream>

int main()
{
    Variable a(3.);
    std::cout << MemoryLogger<Result>::getCurrentAllocatedSize() << std::endl;
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
    std::cout << MemoryLogger<Result>::getCurrentAllocatedSize() << std::endl;
    return 0;
}
