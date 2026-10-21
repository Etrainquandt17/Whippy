#ifndef STD_TR1_BIND_H
#define STD_TR1_BIND_H

// TODO: this follows the names in the game's symbols (bound_func, mem_fn_0, mem_fn_0_c, mem_fn_1, mem_fn_1_c,
// tuple, placeholders::detail::ph), but only covers a member function with up to one argument bound to an
// object and a value, and one without arguments bound to _1 (see info::sequence::Sequence::start). The
// original also has mem_fn_2 and _2.

#include "std/tr1/reference_wrapper.h"

namespace std {
namespace tr1 {

struct nat {};

namespace placeholders {

namespace detail {

template <int N>
struct ph {};

}

extern detail::ph<1> _1;
extern detail::ph<2> _2;

}

template <class T>
struct tuple_param {
    typedef const T& type;
};

template <class T>
struct tuple_param<T&> {
    typedef T& type;
};

template <class T0, class T1 = nat, class T2 = nat, class T3 = nat, class T4 = nat, class T5 = nat, class T6 = nat,
          class T7 = nat, class T8 = nat, class T9 = nat>
class tuple;

// TODO: only tuples of one and two are written; size is not the original's.
template <class T0>
class tuple<T0, nat, nat, nat, nat, nat, nat, nat, nat, nat> {
public:
    enum { size = 1 };

    tuple() {}
    explicit tuple(typename tuple_param<T0>::type t0) : t0_(t0) {}

    T0 t0_;
};

template <class T0, class T1>
class tuple<T0, T1, nat, nat, nat, nat, nat, nat, nat, nat> {
public:
    enum { size = 2 };

    tuple() {}
    tuple(typename tuple_param<T0>::type t0, typename tuple_param<T1>::type t1) : t0_(t0), t1_(t1) {}

    T0 t0_;
    T1 t1_;
};

template <class T0, class T1, class T2>
class tuple<T0, T1, T2, nat, nat, nat, nat, nat, nat, nat> {
public:
    enum { size = 3 };

    tuple() {}
    tuple(typename tuple_param<T0>::type t0, typename tuple_param<T1>::type t1, typename tuple_param<T2>::type t2)
        : t0_(t0), t1_(t1), t2_(t2) {}

    T0 t0_;
    T1 t1_;
    T2 t2_;
};

namespace detail {

template <class R, class T>
class mem_fn_0 {
public:
    explicit mem_fn_0(R (T::*pm)()) : pm_(pm) {}

    R operator()(T& t) const { return (t.*pm_)(); }
    template <class U>
    R operator()(const U& u) const {
        return ((*u).*pm_)();
    }

private:
    R (T::*pm_)();
};

template <class R, class T>
class mem_fn_0_c {
public:
    explicit mem_fn_0_c(R (T::*pm)() const) : pm_(pm) {}

    R operator()(const T& t) const { return (t.*pm_)(); }
    template <class U>
    R operator()(const U& u) const {
        return ((*u).*pm_)();
    }

private:
    R (T::*pm_)() const;
};

template <class R, class T, class A1>
class mem_fn_1 {
public:
    explicit mem_fn_1(R (T::*pm)(A1)) : pm_(pm) {}

    R operator()(T& t, A1 a1) const { return (t.*pm_)(a1); }
    template <class U>
    R operator()(const U& u, A1 a1) const {
        return ((*u).*pm_)(a1);
    }

private:
    R (T::*pm_)(A1);
};

template <class R, class T, class A1>
class mem_fn_1_c {
public:
    explicit mem_fn_1_c(R (T::*pm)(A1) const) : pm_(pm) {}

    R operator()(const T& t, A1 a1) const { return (t.*pm_)(a1); }
    template <class U>
    R operator()(const U& u, A1 a1) const {
        return ((*u).*pm_)(a1);
    }

private:
    R (T::*pm_)(A1) const;
};

template <class R, class T, class A1, class A2>
class mem_fn_2 {
public:
    explicit mem_fn_2(R (T::*pm)(A1, A2)) : pm_(pm) {}

    R operator()(T& t, A1 a1, A2 a2) const { return (t.*pm_)(a1, a2); }
    template <class U>
    R operator()(const U& u, A1 a1, A2 a2) const {
        return ((*u).*pm_)(a1, a2);
    }

private:
    R (T::*pm_)(A1, A2);
};

// TODO: a guess that gives the original's code. function_imp<bool (*)(), F, 0, 0>::operator() turns what
// bound_func::operator()() returns into a bool again, so that is not a bool; what it is, is not known.
template <class R>
struct bound_result {
    typedef int type;
};

template <>
struct bound_result<void> {
    typedef void type;
};

// TODO: the names of bound_value and bound_call are guesses, as is telling the tuples apart by a size.
template <class T>
inline T& bound_value(reference_wrapper<T>& r) {
    return r.get();
}

template <class T>
inline T& bound_value(T& t) {
    return t;
}

template <int N>
struct bound_call;

template <>
struct bound_call<1> {
    template <class R, class F, class Tuple>
    static R call(F& f, Tuple& t) {
        return f(bound_value(t.t0_));
    }
};

template <>
struct bound_call<2> {
    template <class R, class F, class Tuple>
    static R call(F& f, Tuple& t) {
        return f(bound_value(t.t0_), bound_value(t.t1_));
    }
};

// TODO: the name is a guess; nothing of it is left in the symbols. What matters
// is that the call goes through an object that refers to the argument tuple:
// that keeps the tuple's own store (see info::sequence::Sequence::start).
template <class A1>
class bound_args {
public:
    explicit bound_args(const tuple<A1&>& args) : args_(args) {}

    A1& operator()(placeholders::detail::ph<1>) const { return args_.t0_; }

private:
    const tuple<A1&>& args_;
};

// TODO: the name is a guess, like bound_args.
template <class A1, class A2>
class bound_args2 {
public:
    explicit bound_args2(const tuple<A1&, A2&>& args) : args_(args) {}

    A1& operator()(placeholders::detail::ph<1>) const { return args_.t0_; }
    A2& operator()(placeholders::detail::ph<2>) const { return args_.t1_; }

private:
    const tuple<A1&, A2&>& args_;
};

template <class R, class F, class Tuple>
class bound_func {
public:
    bound_func(const F& f, const Tuple& t) : f_(f), t_(t) {}

    typename bound_result<R>::type operator()() { return bound_call<Tuple::size>::template call<R, F, Tuple>(f_, t_); }

    template <class A1>
    R operator()(A1& a1) {
        return call(tuple<A1&>(a1));
    }
    template <class A1, class A2>
    R operator()(A1& a1, A2& a2) {
        return call(tuple<A1&, A2&>(a1, a2));
    }

private:
    template <class A1>
    R call(const tuple<A1&>& args) {
        return f_(bound_args<A1>(args)(t_.t0_));
    }
    template <class A1, class A2>
    R call(const tuple<A1&, A2&>& args) {
        return f_(t_.t0_, bound_args2<A1, A2>(args)(t_.t1_), bound_args2<A1, A2>(args)(t_.t2_));
    }

    F f_;
    Tuple t_;
};

}

template <class R, class T>
inline detail::mem_fn_0<R, T> mem_fn(R (T::*pm)()) {
    return detail::mem_fn_0<R, T>(pm);
}

template <class R, class T>
inline detail::mem_fn_0_c<R, T> mem_fn(R (T::*pm)() const) {
    return detail::mem_fn_0_c<R, T>(pm);
}

template <class R, class T, class A1>
inline detail::mem_fn_1<R, T, A1> mem_fn(R (T::*pm)(A1)) {
    return detail::mem_fn_1<R, T, A1>(pm);
}

template <class R, class T, class A1>
inline detail::mem_fn_1_c<R, T, A1> mem_fn(R (T::*pm)(A1) const) {
    return detail::mem_fn_1_c<R, T, A1>(pm);
}

template <class R, class T, class A1, class A2>
inline detail::mem_fn_2<R, T, A1, A2> mem_fn(R (T::*pm)(A1, A2)) {
    return detail::mem_fn_2<R, T, A1, A2>(pm);
}

template <class R, class T, class B1, class B2, class A1, class A2, class A3>
inline detail::bound_func<R, detail::mem_fn_2<R, T, B1, B2>, tuple<A1, A2, A3> > bind(R (T::*pm)(B1, B2), A1 a1, A2 a2,
                                                                                    A3 a3) {
    return detail::bound_func<R, detail::mem_fn_2<R, T, B1, B2>, tuple<A1, A2, A3> >(mem_fn(pm),
                                                                                      tuple<A1, A2, A3>(a1, a2, a3));
}

template <class R, class T, class B1, class A1, class A2>
inline detail::bound_func<R, detail::mem_fn_1_c<R, T, B1>, tuple<A1, A2> > bind(R (T::*pm)(B1) const, A1 a1, A2 a2) {
    return detail::bound_func<R, detail::mem_fn_1_c<R, T, B1>, tuple<A1, A2> >(mem_fn(pm), tuple<A1, A2>(a1, a2));
}

template <class R, class T, class A1>
inline detail::bound_func<R, detail::mem_fn_0_c<R, T>, tuple<A1> > bind(R (T::*pm)() const, A1 a1) {
    return detail::bound_func<R, detail::mem_fn_0_c<R, T>, tuple<A1> >(mem_fn(pm), tuple<A1>(a1));
}

template <class R, class T, class B1, class A1, class A2>
inline detail::bound_func<R, detail::mem_fn_1<R, T, B1>, tuple<A1, A2> > bind(R (T::*pm)(B1), A1 a1, A2 a2) {
    return detail::bound_func<R, detail::mem_fn_1<R, T, B1>, tuple<A1, A2> >(mem_fn(pm), tuple<A1, A2>(a1, a2));
}

template <class R, class T, class A1>
inline detail::bound_func<R, detail::mem_fn_0<R, T>, tuple<A1> > bind(R (T::*pm)(), A1 a1) {
    return detail::bound_func<R, detail::mem_fn_0<R, T>, tuple<A1> >(mem_fn(pm), tuple<A1>(a1));
}

}}  // namespace std::tr1

#endif
