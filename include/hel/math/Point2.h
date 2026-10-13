#ifndef HEL_MATH_POINT2_H
#define HEL_MATH_POINT2_H

#include "types.h"

namespace hel {
namespace math {

class Point2 {
public:
    Point2(f32 x, f32 y);
    Point2(const Point2& other);

    Point2& operator=(const Point2& other);

    f32 y() const { return mY; }

    static const Point2 ORIGIN;

private:
    f32 mX;
    f32 mY;
};

}
}

#endif
