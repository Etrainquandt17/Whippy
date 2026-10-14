#include "scn/step/GridPos.h"

#include "hel/math/Math.h"

using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {

GridPos::GridPos()
    : mX(0)
    , mY(0) {}

GridPos::GridPos(s32 x, s32 y)
    : mX(x)
    , mY(y) {}

GridPos::GridPos(const Vector2& pos)
    : mX(static_cast<s32>(Math::FloorF(pos.x)))
    , mY(static_cast<s32>(Math::FloorF(pos.y))) {}

Vector2 GridPos::toWorldPos() const {
    return Vector2(static_cast<f32>(mX), static_cast<f32>(mY));
}

Vector2 GridPos::toWorldPosAtCenter() const {
    return (toWorldPos() + GridPos(mX + 1, mY + 1).toWorldPos()) * 0.5f;
}

bool GridPos::isPositivePos() const {
    return mX >= 0 && mY >= 0;
}

}}  // namespace scn::step
