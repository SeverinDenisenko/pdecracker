#pragma once

#include "defines.hpp"

namespace pde
{
template <class T>
class allocator
{
public:
    typedef T value_type;

    [[nodiscard]] static T* allocate(std::size_t n)
    {
        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            return p;
        }

        throw std::bad_alloc();
    }

    static void deallocate(T* p, [[maybe_unused]] std::size_t n) noexcept
    {
        std::free(p);
    }
};
} // namespace pde
