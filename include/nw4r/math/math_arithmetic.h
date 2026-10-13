#ifndef NW4R_MATH_ARITHMETIC_H
#define NW4R_MATH_ARITHMETIC_H

#include "types.h"

extern "C" double floor(double x);

namespace nw4r {

namespace db {

void Warning(const char* file, int line, const char* message, ...);

}

namespace math {

f32 FrSqrt(f32 x);

inline f32 FSqrt(f32 x) {
    if (!(x >= 0.0f)) {
        db::Warning("arithmetic.h", 627, "FSqrt: Input is out of the domain.");
    }
    return x <= 0.0f ? 0.0f : x * FrSqrt(x);
}

inline f32 FFloor(f32 x) {
    return floor(x);
}

}
}

#endif
