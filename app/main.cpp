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

int main()
{
    pde::real dx      = 1.0e-4;
    pde::real dt      = 1.0e-4;
    pde::real a       = 0.99;
    pde::interval x   = {0.0, 1.0};
    pde::interval t   = {0.0, 1.0};
    pde::function eta = [](pde::real x) -> pde::real { return (x >= 0.4 && x <= 0.6) ? 0.8 : 0.4; };

    pde::advection params{.dx = dx, .x = x, .dt = dt, .t = t, .a = a, .eta = eta};
    pde::cir cir(params);
    pde::vector res = cir.solve();

    std::ofstream initial("initial.dat");
    std::ofstream solution("solution.dat");

    auto start = pde::eval(x, eta, dx);
    auto time  = pde::linspace(t, dt);

    write(initial, time, start);
    write(solution, time, res);

    initial.close();
    solution.close();

    return 0;
}
