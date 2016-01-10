#include "FunctionalTests.hpp"
#include "PerformanceTests.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    launchFunctionalTests();

    if (argc > 1)
        launchPerformanceTests(atoi(argv[1]));

    return 0;
}
