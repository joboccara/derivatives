#include "PerformanceTests.hpp"

#include <iostream>

int main()
{
    for (int i = 0; i < 3000; ++i)
    {
        compute_dfds_classic();
    }
    std::cout << "bu" << std::endl;
    //std::cout << "dF/dS classic = " << compute_dfds_classic() << std::endl;
    std::cout << "dF/dS algodiff = " << compute_dfds_algodiff() << std::endl;
    return 0;
}
