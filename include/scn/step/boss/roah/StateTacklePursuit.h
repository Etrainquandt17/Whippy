#ifndef SCN_STEP_BOSS_ROAH_STATETACKLEPURSUIT_H
#define SCN_STEP_BOSS_ROAH_STATETACKLEPURSUIT_H

#include "gobj/MoveParam.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/roah/StateTackle.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateTacklePursuit : public StateBase {
public:
    struct Config {
        u32 _0;
        gobj::MoveParamAccel _4;
    };

    StateTacklePursuit(Boss* boss, Config config, StateTackle::Config tackleConfig);
    virtual ~StateTacklePursuit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFadeEndCount;
    u32 mCount;
    Config mConfig;
    StateTackle::Config mTackleConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
