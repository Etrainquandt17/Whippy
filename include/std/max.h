#ifndef STD_MAX_H
#define STD_MAX_H

namespace std {

template <typename T>
inline const T& max(const T& a, const T& b) {
    return a < b ? b : a;
}

}

#endif
