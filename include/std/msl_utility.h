#ifndef STD_MSL_UTILITY_H
#define STD_MSL_UTILITY_H

// The parts of the Metrowerks utility header that std::map needs.

namespace Metrowerks {

namespace details {

template <class T1, class T2, int N>
class compressed_pair_imp;

// TODO: only the form that stores both members is written. The library picks
// another one when a member is an empty class.
template <class T1, class T2>
class compressed_pair_imp<T1, T2, 0> {
public:
    compressed_pair_imp() {}
    compressed_pair_imp(T1 x, T2 y) : first_(x), second_(y) {}
    explicit compressed_pair_imp(T1 x) : first_(x) {}

    T1& first() { return first_; }
    const T1& first() const { return first_; }
    T2& second() { return second_; }
    const T2& second() const { return second_; }

private:
    T1 first_;
    T2 second_;
};

}

template <class T1, class T2>
class compressed_pair : private details::compressed_pair_imp<T1, T2, 0> {
    typedef details::compressed_pair_imp<T1, T2, 0> base;

public:
    compressed_pair() {}
    compressed_pair(T1 x, T2 y) : base(x, y) {}
    explicit compressed_pair(T1 x) : base(x) {}

    T1& first() { return base::first(); }
    const T1& first() const { return base::first(); }
    T2& second() { return base::second(); }
    const T2& second() const { return base::second(); }
};

template <class T, T N>
struct number {};

template <class T, class Allocator, class Size = number<unsigned long, 1> >
class alloc_ptr {
public:
    typedef T* pointer;

    alloc_ptr(pointer p, Allocator a) : ptr_(a, p) {}

    ~alloc_ptr() {
        if (get()) {
            ptr_.first().deallocate(get(), 1);
        }
    }

    pointer get() const;
    pointer operator->() const { return get(); }

    pointer release() {
        pointer tmp = get();
        ptr_.second() = 0;
        return tmp;
    }

private:
    compressed_pair<Allocator, pointer> ptr_;
};

template <class T, class Allocator, class Size>
typename alloc_ptr<T, Allocator, Size>::pointer alloc_ptr<T, Allocator, Size>::get() const {
    // Written as a plain return it is expanded at every use; the library's stays a call.
    pointer p = ptr_.second();
    return p;
}

}

#endif
