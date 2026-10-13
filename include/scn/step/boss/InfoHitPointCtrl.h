#ifndef SCN_STEP_BOSS_INFOHITPOINTCTRL_H
#define SCN_STEP_BOSS_INFOHITPOINTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class InfoHitPointCtrl {
public:
    InfoHitPointCtrl(Boss& boss);
    ~InfoHitPointCtrl();

    f32 getHitPointRate() const;
    bool isInfoHitPointZero() const;
    void setZero(u32 value);
    void unsetZero();
    void setFull(u32 value);
    void unsetFull();

private:
    Boss& mBoss;
    u32 mZero;
    u32 mFull;
};

}}}  // namespace scn::step::boss

#endif
