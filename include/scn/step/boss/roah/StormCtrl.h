#ifndef SCN_STEP_BOSS_ROAH_STORMCTRL_H
#define SCN_STEP_BOSS_ROAH_STORMCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

}

class Boss;

namespace roah {

class StormCtrl {
public:
    StormCtrl(Boss& boss);

    void update();
    void toValid(u32 time);
    void toInvalid();
    bool isDamageTiming() const;

private:
    Boss& mBoss;
    bool mIsValid;
    u32 mCount;
    u32 mTime;
};

}}}}  // namespace scn::step::boss::roah

#endif
