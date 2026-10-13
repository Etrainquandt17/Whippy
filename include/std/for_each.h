#ifndef STD_FOR_EACH_H
#define STD_FOR_EACH_H

namespace std {

template <class InputIterator, class Function>
inline Function for_each(InputIterator first, InputIterator last, Function f) {
    for (; first != last; ++first) {
        f(*first);
    }
    return f;
}

}  // namespace std

#endif
