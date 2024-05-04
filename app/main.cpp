#include <iostream>

#include "vector.hpp"

int main()
{
    pde::vector<double> vec{0.1, 0.4, 1.5};
    std::cout << vec[0] << std::endl;
    return 0;
}
