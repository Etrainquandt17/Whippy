#ifndef HEL_GEO_RECT_H
#define HEL_GEO_RECT_H

#include "types.h"

namespace hel {

namespace math {
class Vector2;
}

namespace geo {

class Rect {
public:
    Rect();
    Rect(f32, f32, f32, f32);
    Rect(const Rect& other);
    ~Rect();

    Rect& operator=(const Rect& other);
    Rect operator+(const Rect& other) const;
    Rect operator-(const Rect& other) const;
    Rect operator*(f32 scale) const;

    void set(f32 minY, f32 maxY, f32 minX, f32 maxX);
    void trans(f32 x, f32 y);
    const math::Vector2 getCenter() const;
    f32 getWidth() const;
    f32 getHeight() const;
    bool isInclude(f32 x, f32 y) const;
    bool isIntersect(const Rect& other) const;
    void adjustAspectShrink(f32 aspect);
    void transInternal(const Rect& other);
    void margeUnion(const Rect& other);

    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
};

}
}

#endif
