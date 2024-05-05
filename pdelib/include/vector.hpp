#pragma once

#include <iomanip>
#include <iostream>

#include "allocator.hpp"
#include "defines.hpp"
#include "isclose.hpp"

namespace pde
{

template <class T, class Allocator = allocator<T>>
class arbitrary_vector
{
public:
    explicit arbitrary_vector(size_t size)
        : size_(size)
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
    }

    arbitrary_vector()
        : size_(0)
        , data_(nullptr)
    {
    }

    arbitrary_vector(const arbitrary_vector& other)
        : size_(other.size_)
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
        memcpy(data_, other.data_, sizeof(T) * size_);
    }

    arbitrary_vector(arbitrary_vector&& other)
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    arbitrary_vector(std::initializer_list<T> l)
        : size_(l.size())
        , data_(reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * size_)))
    {
        auto iter = l.begin();
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = *iter;
            ++iter;
        }
    }

    friend bool operator==(const arbitrary_vector& a, const arbitrary_vector& b)
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

    friend void swap(arbitrary_vector& a, arbitrary_vector& b)
    {
        std::swap(a.size_, b.size_);
        std::swap(a.data_, b.data_);
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

    ~arbitrary_vector()
    {
        Allocator::deallocate(data_, size_);
    }

    friend std::ostream& operator<<(std::ostream& stream, const arbitrary_vector& a)
    {
        for (size_t i = 0; i < a.size() - 1; ++i) {
            stream << a[i] << " ";
        }
        stream << a[a.size() - 1] << "\n";
        return stream;
    }

private:
    size_t size_{0};
    T* data_{nullptr};
};

using vector = arbitrary_vector<real>;

} // namespace pde
