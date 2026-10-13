#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_LANDCTRL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_LANDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}
class Boss;
namespace galactaknight {

class LandCtrl {
public:
    LandCtrl(Boss& boss);

    f32 getCenterX() const;
    f32 getFloorY() const;
    f32 getWidth() const;
    f32 getFarEdgeX(f32 margin) const;
    f32 getFrontOutSidePosX() const;
    bool isGround() const;

private:
    Boss& mBoss;
    f32 mCenterX;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
