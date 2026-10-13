#ifndef SCN_STEP_BOSS_HRD3_LANDCTRL_H
#define SCN_STEP_BOSS_HRD3_LANDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

}
class Boss;
namespace hrd3 {

class LandCtrl {
public:
    LandCtrl(Boss& boss);

    f32 getCenterX() const;
    f32 getWidth() const;
    f32 getFloorY() const;
    f32 getAdjustX(f32 x, f32 margin) const;
    f32 getAdjustX(f32 x, f32 left, f32 right, bool isRight) const;

private:
    Boss& mBoss;
    f32 mCenterX;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
