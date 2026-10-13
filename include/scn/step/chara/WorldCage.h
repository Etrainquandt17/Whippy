#ifndef SCN_STEP_CHARA_WORLDCAGE_H
#define SCN_STEP_CHARA_WORLDCAGE_H

#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members and the other functions.
class WorldCage {
public:
    void proc();
    void setIsValid(bool isValid);
    void setIsOnlyOut(bool isOnlyOut);
    void changePadding(f32, f32);
    bool isValid() const;
    bool isCorrected() const;
    bool isCorrectedByMovedRect() const;
    bool isTooFar() const;
    hel::math::Vector2 getCorrectedDiff() const;
    hel::geo::Rect getLimitRect() const;
};

}}}  // namespace scn::step::chara

#endif
