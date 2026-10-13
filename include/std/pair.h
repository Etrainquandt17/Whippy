#ifndef STD_PAIR_H
#define STD_PAIR_H

namespace std {

template <class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    pair() : first(), second() {}
    pair(const T1& x, const T2& y) : first(x), second(y) {}

    template <class U, class V>
    pair(const pair<U, V>& p) : first(p.first), second(p.second) {}

    T1 first;
    T2 second;
};

template <class T>
struct less {
    bool operator()(const T& x, const T& y) const {
        return x < y;
    }
};

}

#endif
