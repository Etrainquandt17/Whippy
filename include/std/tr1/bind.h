#ifndef STD_TR1_BIND_H
#define STD_TR1_BIND_H

// TODO: this follows the names in the game's symbols (bound_func, mem_fn_0,
// tuple, placeholders::detail::ph), but only covers a member function without
// arguments bound to _1 (see info::sequence::Sequence::start).

namespace std {
namespace tr1 {

struct nat {};

namespace placeholders {

namespace detail {

template <int N>
struct ph {};

}

extern detail::ph<1> _1;

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
class tuple {
public:
    tuple() {}
    explicit tuple(typename tuple_param<T0>::type t0) : t0_(t0) {}

    T0 t0_;
};

namespace detail {

template <class R, class T>
class mem_fn_0 {
public:
    explicit mem_fn_0(R (T::*pm)()) : pm_(pm) {}

    R operator()(T* p) const { return (p->*pm_)(); }

private:
    R (T::*pm_)();
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

template <class R, class F, class Tuple>
class bound_func {
public:
    bound_func(const F& f, const Tuple& t) : f_(f), t_(t) {}

    template <class A1>
    R operator()(A1& a1) {
        return call(tuple<A1&>(a1));
    }

private:
    template <class A1>
    R call(const tuple<A1&>& args) {
        return f_(bound_args<A1>(args)(t_.t0_));
    }

    F f_;
    Tuple t_;
};

}

template <class R, class T>
inline detail::mem_fn_0<R, T> mem_fn(R (T::*pm)()) {
    return detail::mem_fn_0<R, T>(pm);
}

template <class R, class T, class A1>
inline detail::bound_func<R, detail::mem_fn_0<R, T>, tuple<A1> > bind(R (T::*pm)(), A1 a1) {
    return detail::bound_func<R, detail::mem_fn_0<R, T>, tuple<A1> >(mem_fn(pm), tuple<A1>(a1));
}

}
}

#endif
