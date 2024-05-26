#include "cir.hpp"

namespace pde
{
cir::cir(advection eq)
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

vector cir::solve(real t)
{
    if (a_ > 0.0) {
        positive(t);
    } else {
        nagative(t);
    }

    return u0_;
}

void cir::positive(real t)
{
    size_t n = (size_t)abs((t - t_.a) / dt_);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 1; j < u_.size(); ++j) {
            u_[j] = u0_[j] - cfl_ * (u0_[j] - u0_[j - 1]);
        }
        u_[0] = u0_[u_.size() - 1];

        swap(u_, u0_);
    }
}

void cir::nagative(real t)
{
    size_t n = (size_t)abs((t - t_.a) / dt_);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < u_.size() - 1; ++j) {
            u_[j] = u0_[j] - cfl_ * (u0_[j] - u0_[j + 1]);
        }
        u_[u_.size() - 1] = u0_[0];

        swap(u_, u0_);
    }
}
} // namespace pde
