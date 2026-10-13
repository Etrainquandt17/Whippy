#ifndef SCN_STEP_CORE_AREAOPERATION_H
#define SCN_STEP_CORE_AREAOPERATION_H

#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace core {

// TODO: members.
class AreaOperation {
public:
    AreaOperation();

    u32 getUnusedAdditionalVelocityID();
    u32 createAdditionalVelocity(const hel::geo::Rect& rect);
    void setAdditionalVelocity(u32 id, const hel::math::Vector2& velocity);
    hel::math::Vector2 getAdditionalVelocity(const hel::math::Vector2& pos) const;
    void clearAllAdditionalVelocity();
    u32 getUnusedFrozenAreaID();
    u32 createFrozenArea(const hel::geo::Rect& rect);
    void removeFrozenArea(u32 id);
    bool isInFrozenArea(const hel::math::Vector2& pos) const;
};

}
}
}

#endif
