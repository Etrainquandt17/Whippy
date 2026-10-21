#ifndef STD_TR1_FUNCTION_H
#define STD_TR1_FUNCTION_H

// TODO: only what the game's symbols show of it: a function without arguments that is made from a callable,
// held, copied and called. The original also has function_imp<R (*)(A1, A2), F, 0, 1>.

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

// TODO: the names of these two are guesses. The constructor from a callable has a second parameter that is a
// void* in its symbol; it keeps the literal 0 for function(int nat::*).
template <bool B, class T = void>
struct restrict_to {};

template <class T>
struct restrict_to<true, T> {
    typedef T type;
};

template <class T>
struct is_integral {
    static const bool value = false;
};

template <>
struct is_integral<int> {
    static const bool value = true;
};

// TODO: what the two flags stand for is not known.
template <class F, class C, bool A, bool B>
class function_imp;

template <class R, class C>
class function_imp<R (*)(), C, false, false> : public function_base<R (*)()> {
public:
    explicit function_imp(C f) : f_(f) {}
    virtual function_base<R (*)()>* clone() const { return new function_imp(*this); }
    virtual function_base<R (*)()>* clone(void* buffer) const { return new (buffer) function_imp(*this); }
    virtual R operator()() { return static_cast<R>(f_()); }

private:
    C f_;
};

template <class T>
inline void swap(T& a, T& b) {
    T t = a;
    a = b;
    b = t;
}

template <class R, class A1, class A2>
class function_base<R (*)(A1, A2)> {
public:
    virtual ~function_base() {}
    virtual function_base* clone() const = 0;
    virtual function_base* clone(void* buffer) const = 0;
    virtual R operator()(A1, A2) = 0;
};

template <class R, class A1, class A2, class C>
class function_imp<R (*)(A1, A2), C, false, true> : public function_base<R (*)(A1, A2)> {
public:
    explicit function_imp(C f) : f_(f) {}
    virtual function_base<R (*)(A1, A2)>* clone() const { return new function_imp(*this); }
    virtual function_base<R (*)(A1, A2)>* clone(void* buffer) const { return new (buffer) function_imp(*this); }
    virtual R operator()(A1 a1, A2 a2) { return f_(a1, a2); }

private:
    C f_;
};

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
    template <class C>
    function(C f, typename detail::restrict_to<!detail::is_integral<C>::value>::type* = 0) : f_(0) {
        if (!is_empty(f)) {
            f_ = new detail::function_imp<R (*)(), C, false, false>(f);
        }
    }
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
    static bool is_empty(...) { return false; }

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

template <class R, class A1, class A2>
class function<R(A1, A2)> {
    typedef detail::function_base<R (*)(A1, A2)> base;
    struct nat {
        int _0;
    };
    struct bool_type {
        int _0;
    };

public:
    function(int nat::* = 0) : f_(0) {}
    template <class C>
    function(C f, typename detail::restrict_to<!detail::is_integral<C>::value>::type* = 0) : f_(0) {
        if (!is_empty(f)) {
            f_ = new detail::function_imp<R (*)(A1, A2), C, false, true>(f);
        }
    }
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

    R operator()(A1 a1, A2 a2) const {
        if (f_ == 0) {
            detail::throw_bad_function_call<1>();
        }
        return (*f_)(a1, a2);
    }

private:
    static bool is_empty(...) { return false; }

    base* f_;
    R (*buf0_)(A1, A2);
    R (**buf1_)(A1, A2);
};

template <class R, class A1, class A2>
function<R(A1, A2)>::~function() {
    if (f_ == reinterpret_cast<base*>(&buf0_)) {
        f_->~base();
    } else if (f_ != 0) {
        delete f_;
    }
}

template <class R, class A1, class A2>
function<R(A1, A2)>& function<R(A1, A2)>::operator=(const function& other) {
    function tmp(other);
    swap(tmp);
    return *this;
}

}}  // namespace std::tr1

#endif
