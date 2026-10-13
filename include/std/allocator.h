#ifndef STD_ALLOCATOR_H
#define STD_ALLOCATOR_H

#include "std/msl_utility.h"
#include "std/new.h"

namespace std {

// TODO: only what std::map needs.
template <class T>
class allocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef unsigned long size_type;

    template <class U>
    struct rebind {
        typedef allocator<U> other;
    };

    allocator() {}
    template <class U>
    allocator(const allocator<U>&) {}

    pointer allocate(size_type n) { return static_cast<pointer>(::operator new(n * sizeof(T))); }
    void deallocate(pointer p, size_type) { ::operator delete(p); }
};

}

namespace Metrowerks {

// The empty allocator takes no room in the pair.
template <class U, class T2>
class compressed_pair<std::allocator<U>, T2> : private std::allocator<U> {
public:
    compressed_pair() {}
    compressed_pair(std::allocator<U> x, T2 y) : std::allocator<U>(x), second_(y) {}
    explicit compressed_pair(std::allocator<U> x) : std::allocator<U>(x) {}

    std::allocator<U>& first() { return *this; }
    const std::allocator<U>& first() const { return *this; }
    T2& second() { return second_; }
    const T2& second() const { return second_; }

private:
    T2 second_;
};

}

#endif
