#ifndef SCN_STEP_BOSS_GOLIATH_ELEVATIONCTRL_H
#define SCN_STEP_BOSS_GOLIATH_ELEVATIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class ElevationCtrl {
public:
    ElevationCtrl(Boss& boss);

    void update();
    void setElevX(f32 elev);
    void setElevZ(f32 elev);
    void resetElev();
    void setIntpRateX(f32 rate);
    void setIntpRateZ(f32 rate);
    void resetIntpRate();
    f32 getElevX() const;
    f32 getElevZ() const;

private:
    Boss& mBoss;
    f32 mElevX;
    f32 mTargetElevX;
    f32 mElevZ;
    f32 mTargetElevZ;
    f32 mIntpRateX;
    f32 mIntpRateZ;
};

}}}}  // namespace scn::step::boss::goliath

#endif
