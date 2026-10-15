#ifndef SCN_STEP_BOSS_GOLIATH_HAIRCTRL_H
#define SCN_STEP_BOSS_GOLIATH_HAIRCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class HairCtrl {
public:
    HairCtrl(Boss& boss);

    void update();
    void setAngry(bool isAngry);

private:
    Boss& mBoss;
    bool mIsAngry;
    f32 mPhaseY;
    f32 mPhaseZ;
};

}}}}  // namespace scn::step::boss::goliath

#endif
