#pragma once

#include "defines.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace pde
{

// Courant–Friedrichs–Lewy condition
real cfl(real a, real dt, real dx)
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
    cir(advection eq)
        : dx_(eq.dx)
        , x_(eq.x)
        , dt_(eq.dt)
        , t_(eq.t)
        , a_(eq.a)
        , cfl_(cfl(a_, dt_, dx_))
        , u0_(eval(x_, eq.eta, dx_))
        , u_(zeros(u0_.size()))
    {
    }

    vector solve()
    {
        if (a_ > 0.0) {
            positive();
        } else {
            nagative();
        }

        return u0_;
    }

private:
    void positive()
    {
        size_t n = (size_t)abs(t_.len() / dt_);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 1; j < u_.size(); ++j) {
                u_[j] = u0_[j] - cfl_ * (u0_[j] - u0_[j - 1]);
            }
            u_[0] = u0_[n - 1];

            swap(u_, u0_);
        }
    }

    void nagative()
    {
        size_t n = (size_t)abs(t_.len() / dt_);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < u_.size() - 1; ++j) {
                u_[j] = u0_[j] - cfl_ * (u0_[j + 1] - u0_[j]);
            }
            u_[n - 1] = u0_[0];

            swap(u_, u0_);
        }
    }

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
