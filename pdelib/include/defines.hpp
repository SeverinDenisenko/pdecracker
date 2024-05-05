#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

#include <functional>
#include <memory>

namespace pde
{
using real = double;

using function = std::function<real(real)>;

template <typename T>
struct arbitrary_interval {
    T a;
    T b;

    T len()
    {
        return b - a;
    }
};

using interval = arbitrary_interval<real>;

} // namespace pde
