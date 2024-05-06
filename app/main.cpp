#include <fstream>
#include <iostream>

#include "cir.hpp"
#include "defines.hpp"
#include "utils.hpp"
#include "vector.hpp"

void write(std::ostream& stream, pde::vector& t, pde::vector& x)
{
    stream << "t x\n";
    for (size_t i = 0; i < t.size(); ++i) {
        stream << std::setprecision(4) << t[i] << " " << x[i] << "\n";
    }
}

// c = 0.6
// c = 0.9
// c = 1.0
// nx = 32

// nx = 32
// nx = 64
// nx = 128
// c = 0.9
int main()
{
    pde::interval x   = {0.0, 1.0};
    pde::interval t   = {0.0, 1.0};
    pde::real dist    = 0.0;
    pde::real a       = 1.0;
    pde::real c       = 0.99;
    size_t steps      = 1024;
    pde::real dx      = x.len() / steps;
    pde::real dt      = pde::dt(a, c, dx);
    pde::function eta = [](pde::real x) -> pde::real { return (x >= 0.4 && x <= 0.6) ? 0.8 : 0.4; };

    pde::advection params{.dx = dx, .x = x, .dt = dt, .t = t, .a = a, .eta = eta};
    pde::cir cir(params);
    pde::vector res = cir.solve(dist);

    std::ofstream initial("initial.dat");
    std::ofstream solution("solution.dat");
    std::ofstream analitycal("analitycal.dat");

    auto start = pde::eval(x, eta, dx);
    auto pos   = pde::linspace(x, dx);
    auto ansol = pde::eval({0.0 - a * dist, 1.0 - a * dist}, eta, dx);

    write(initial, pos, start);
    write(solution, pos, res);
    write(analitycal, pos, ansol);

    initial.close();
    solution.close();
    analitycal.close();

    return 0;
}
