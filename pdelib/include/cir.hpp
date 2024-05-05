#pragma once

#include "defines.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace pde
{

// Courant–Friedrichs–Lewy condition
real inline cfl(real a, real dt, real dx)
{
    return a * dt / dx;
}

// 1D-advection equation parameters
struct advection {
    real dx;
    interval x;
    real dt;
    interval t;
    real a;
    function eta;
};

// Trivial Courant-Isaacson-Rees solver
class cir
{
public:
    cir(advection eq);

    vector solve();

private:
    void positive();

    void nagative();

private:
    real dx_;
    interval x_;
    real dt_;
    interval t_;
    real a_;
    real cfl_;

    vector u0_;
    vector u_;
};
} // namespace pde
