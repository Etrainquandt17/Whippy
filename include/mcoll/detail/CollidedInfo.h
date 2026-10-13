#ifndef MCOLL_DETAIL_COLLIDEDINFO_H
#define MCOLL_DETAIL_COLLIDEDINFO_H

#include "hel/math/Vector2.h"
#include "mcoll/detail/CollideTarget.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: the mcoll::detail::ActorInfo at 4 (0x14 bytes), the float at 0x40 and the other functions.
class CollidedInfo {
public:
    CollidedInfo();
    CollidedInfo(const CollidedInfo& other);

    bool isValid() const;
    CollideTarget collideTarget() const;
    hel::math::Vector2 intersectPos() const;
    MoveGridGroupId groupId() const;
    hel::math::Vector2 landVelocity() const;

private:
    bool mIsValid;
    u32 _4[5];
    CollideTarget mCollideTarget;
    hel::math::Vector2 mIntersectPos;
    f32 _40;
    u32 mGroupId;
    hel::math::Vector2 mLandVelocity;
};

}}  // namespace mcoll::detail

#endif
