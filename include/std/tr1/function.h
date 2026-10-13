#ifndef STD_TR1_FUNCTION_H
#define STD_TR1_FUNCTION_H

// TODO: only what the game's symbols show of it: a function without arguments that is held, copied and
// called (see util::Delegate). Nothing here makes one from a callable yet.

#include "std/tree.h"

namespace std {
namespace tr1 {

namespace detail {

template <int N>
void throw_bad_function_call() {
    __msl_error("bad_function_call");
}

template <class F>
class function_base;

template <class R>
class function_base<R (*)()> {
public:
    virtual ~function_base() {}
    virtual function_base* clone() const = 0;
    virtual function_base* clone(void* buffer) const = 0;
    virtual R operator()() = 0;
};

template <class T>
inline void swap(T& a, T& b) {
    T t = a;
    a = b;
    b = t;
}

}

template <class F>
class function;

template <class R>
class function<R()> {
    typedef detail::function_base<R (*)()> base;
    struct nat {
        int _0;
    };
    struct bool_type {
        int _0;
    };

public:
    function(int nat::* = 0) : f_(0) {}
    function(const function& other) : f_(0) {
        if (other.f_ != 0) {
            if (other.f_ == reinterpret_cast<const base*>(&other.buf0_)) {
                f_ = other.f_->clone(&buf0_);
            } else {
                f_ = other.f_->clone();
            }
        }
    }
    function& operator=(const function& other);
    ~function();

    void swap(function& other) {
        detail::swap(f_, other.f_);
        detail::swap(buf0_, other.buf0_);
        detail::swap(buf1_, other.buf1_);
        if (other.f_ == reinterpret_cast<base*>(&buf0_)) {
            other.f_ = reinterpret_cast<base*>(&other.buf0_);
        }
        if (f_ == reinterpret_cast<base*>(&other.buf0_)) {
            f_ = reinterpret_cast<base*>(&buf0_);
        }
    }

    bool empty() const { return f_ == 0; }
    operator int bool_type::*() const { return f_ ? &bool_type::_0 : 0; }

    R operator()() const {
        if (f_ == 0) {
            detail::throw_bad_function_call<1>();
        }
        return (*f_)();
    }

private:
    base* f_;
    // TODO: what the two words of the buffer are is not known. They are swapped one by one, each with a swap
    // of its own that no other function<> shares, so their types depend on R.
    R (*buf0_)();
    R (**buf1_)();
};

template <class R>
function<R()>::~function() {
    if (f_ == reinterpret_cast<base*>(&buf0_)) {
        f_->~base();
    } else if (f_ != 0) {
        delete f_;
    }
}

template <class R>
function<R()>& function<R()>::operator=(const function& other) {
    function tmp(other);
    swap(tmp);
    return *this;
}

}
}

#endif
