#include <iostream>

#include "cir.hpp"
#include "defines.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace pde
{
} // namespace pde

int main()
{
    pde::real dx      = 1.0e-3;
    pde::real dt      = 1.0e-3;
    pde::real a       = -0.98;
    pde::interval x   = {0.0, 1.0};
    pde::interval t   = {0.0, 1.0};
    pde::function eta = [](pde::real x) -> pde::real { return (x >= 0.4 && x <= 0.6) ? 0.8 : 0.4; };

    pde::advection params{.dx = dx, .x = x, .dt = dt, .t = t, .a = a, .eta = eta};
    pde::cir cir(params);
    pde::vector res = cir.solve();

    std::cout << pde::cfl(a, dt, dx) << std::endl;
    std::cout << pde::eval(x, eta, dx) << std::endl;
    std::cout << res << std::endl;
    return 0;
}
