#pragma once

#include "defines.hpp"
#include "vector.hpp"

namespace pde
{
real lerp(interval i, real t)
{
    return (i.b - i.a) * t + i.a;
}

real abs(real x)
{
    return (x >= 0) ? x : -x;
}

vector eval(interval domain, function f, real delta)
{
    size_t len = (size_t)abs((domain.b - domain.a) / delta);
    vector res(len);

    for (size_t i = 0; i < len; ++i) {
        res[i] = f(lerp(domain, (real)i / len));
    }

    return res;
}

vector zeros(size_t len)
{
    vector res(len);
    for (size_t i = 0; i < len; ++i) {
        res[i] = 0.0;
    }
    return res;
}

vector linspace(interval domain, real delta)
{
    size_t len = (size_t)abs((domain.b - domain.a) / delta);
    vector res(len);
    for (size_t i = 0; i < len; ++i) {
        res[i] = lerp(domain, (real)i / len);
    }
    return res;
}

} // namespace pde