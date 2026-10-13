#include "scn/step/weapon/Desc.h"

namespace scn {
namespace step {
namespace weapon {

Desc::Desc()
    : mKind(KIND_0)
    , mVariation(0)
    , mFlag(ostop::FLAG_0)
    , mPos(hel::math::Vector2::ZERO)
    , _14(hel::math::Vector2::ZERO)
    , _1c(hel::math::Vector2::ZERO)
    , _24(hel::math::Vector2::ZERO)
    , _2c(false)
    , _2d(false)
    , _2e(false)
    , _2f(false)
    , _30(8)
    , mOwner(0) {}

Desc::Desc(Kind kind, u32 variation, ostop::Flag flag, const hel::math::Vector2& pos, const hel::math::Vector2& _14, ::ocoll::Owner& owner)
    : mKind(kind)
    , mVariation(variation)
    , mFlag(flag)
    , mPos(pos)
    , _14(pos)
    , _1c(_14)
    , _24(pos)
    , _2c(false)
    , _2d(false)
    , _2e(false)
    , _2f(false)
    , _30(8)
    , mOwner(&owner) {}

Desc::Desc(Kind kind, u32 variation, ostop::Flag flag, const hel::math::Vector2& pos, const hel::math::Vector2& _14, const hel::math::Vector2& _1c,
           ::ocoll::Owner& owner)
    : mKind(kind)
    , mVariation(variation)
    , mFlag(flag)
    , mPos(pos)
    , _14(_14)
    , _1c(_1c)
    , _24(pos)
    , _2c(false)
    , _2d(false)
    , _2e(false)
    , _2f(false)
    , _30(8)
    , mOwner(&owner) {}

}}}  // namespace scn::step::weapon
