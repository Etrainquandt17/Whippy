#include "hel/math/Point2.h"

namespace hel {
namespace math {

const Point2 Point2::ORIGIN = Point2(0.0f, 0.0f);

Point2::Point2(f32 x, f32 y)
    : mX(x)
    , mY(y) {}

}}  // namespace hel::math
