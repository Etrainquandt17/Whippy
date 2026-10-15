#ifndef SCN_STEP_BOSS_GOLIATH_LANDCTRL_H
#define SCN_STEP_BOSS_GOLIATH_LANDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class LandCtrl {
public:
    LandCtrl(Boss& boss);

    f32 getFloorY() const;
    f32 getFloorYWithBump() const;
    f32 getWidth() const;
    f32 getWallDepth() const;
    f32 getCenterX() const;
    f32 getOppositeWallX() const;
    f32 getFaceToFaceWallX() const;
    f32 getAdjustX(f32 x, f32 margin) const;
    int getLevel() const;
    bool isMaxLevel() const;
    int getMaxLevelOnBattle() const;
    void levelUp();

private:
    Boss& mBoss;
    u32 mLevel;
    f32 mCenterX;
};

}}}}  // namespace scn::step::boss::goliath

#endif
