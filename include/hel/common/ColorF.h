#ifndef HEL_COMMON_COLORF_H
#define HEL_COMMON_COLORF_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace hel {
namespace common {

// TODO: the other functions.
class ColorF {
public:
    ColorF(f32 r_, f32 g_, f32 b_, f32 a_) : r(r_), g(g_), b(b_), a(a_) {}

    void set(f32 r_, f32 g_, f32 b_, f32 a_) {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }

    ColorF& operator*=(f32 scale) {
        r *= scale;
        g *= scale;
        b *= scale;
        a *= scale;
        return *this;
    }

    // TODO: a guess. The original copies the colour by words, scales the copy in place and copies the result
    // member by member; a value parameter and a returned reference give that.
    static ColorF Scale(ColorF color, f32 scale) { return color *= scale; }

    GXColor toGXColorAsNormal() const {
        ColorF color = Scale(*this, 255.0f);
        GXColor result;
        result.r = color.r;
        result.g = color.g;
        result.b = color.b;
        result.a = color.a;
        return result;
    }

    GXColor toGXColor() const {
        GXColor result;
        result.r = r;
        result.g = g;
        result.b = b;
        result.a = a;
        return result;
    }

    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

}
}

#endif
