#ifndef STD_CMATH_H
#define STD_CMATH_H

// TODO: replace with the standard library's own header once the project has it.

extern "C" {

double tan(double x);
double sin(double x);
double cos(double x);
double acos(double x);
float acosf(float x);
float sinf(float x);
float cosf(float x);

}

inline double fabs(double x) {
    return __fabs(x);
}

namespace std {

inline float fabs(float x) {
    return static_cast<float>(::fabs(x));
}

}

inline float tanf(float x) {
    return static_cast<float>(tan(x));
}

#endif
