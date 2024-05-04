#pragma once

#include <concepts>

#include "allocator.hpp"
#include "defines.hpp"
#include "isclose.hpp"

namespace pde
{

template <class T, class Allocator = allocator<T>>
class vector
{
public:
    explicit vector(size_t size)
        : size_(size)
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
    }

    vector()
        : size_(0)
        , data_(nullptr)
    {
    }

    vector(const vector& other)
        : size_(other.size_)
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
        memcpy(data_, other.data_, sizeof(T) * size_);
    }

    vector(vector&& other)
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    vector(std::initializer_list<T> l)
        : size_(l.size())
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
        auto iter = l.begin();
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = *iter;
            ++iter;
        }
    }

    friend bool operator==(const vector& a, const vector& b)
    {
        if (a.size() != b.size()) {
            return false;
        }

        for (size_t i = 0; i < a.size(); ++i) {
            if (!isclose(a[i], b[i])) {
                return false;
            }
        }

        return true;
    }

    const T& operator[](size_t i) const
    {
        assert(i < size_ && "Out of bounds!");
        return *(data_ + i);
    }

    T& operator[](size_t i)
    {
        assert(i < size_ && "Out of bounds!");
        return *(data_ + i);
    }

    size_t size() const
    {
        return size_;
    }

    T* data()
    {
        return data_;
    }

    const T* data() const
    {
        return data_;
    }

    ~vector()
    {
        Allocator::deallocate(data_, size_);
    }

private:
    size_t size_{0};
    T* data_{nullptr};
};

} // namespace pde
