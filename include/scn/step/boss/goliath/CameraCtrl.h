#ifndef SCN_STEP_BOSS_GOLIATH_CAMERACTRL_H
#define SCN_STEP_BOSS_GOLIATH_CAMERACTRL_H

#include "hel/geo/Rect.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class CameraCtrl {
public:
    CameraCtrl(Boss& boss);

    void update();
    void init();
    void startAppear();
    void startAppearEnd();
    void startGroundChange(u32 time);
    void startDeadGroundChange();

private:
    void initMoveLimit();
    void groundChangeCommonSetting();
    void updateGroundChange();
    void updateDeadGroundChange();
    void updateDeadGroundChangeEnd();
    void updateMoveLimit();

    Boss& mBoss;
    u32 mFrame;
    u32 mTime;
    u32 mState;
    hel::geo::Rect mStartRect;
    hel::geo::Rect mGoalRect;
    hel::geo::Rect mStartLimit;
    hel::geo::Rect mGoalLimit;
    f32 mOffsetY;
    f32 mSpeedY;
};

}}}}  // namespace scn::step::boss::goliath

#endif
