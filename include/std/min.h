#ifndef STD_MIN_H
#define STD_MIN_H

namespace std {

template <typename T>
inline const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

}

#endif
