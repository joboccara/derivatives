#include "PerformanceTests.hpp"

#include <iostream>

int main()
{
    //std::cout << "dF/dS classic = " << compute_dfds_classic() << std::endl;
    std::cout << "dF/dS algodiff = " << compute_dfds_algodiff() << std::endl;
    return 0;
}
