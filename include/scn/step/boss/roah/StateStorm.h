#ifndef SCN_STEP_BOSS_ROAH_STATESTORM_H
#define SCN_STEP_BOSS_ROAH_STATESTORM_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

enum StormKind {
    StormKind_UpDown,
    StormKind_Circle
};

class StateStorm : public StateBase {
public:
    struct Config {
        u32 _0;
        f32 _4;
        StormKind _8;
    };

    StateStorm(Boss* boss, Config config);
    virtual ~StateStorm();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool isOnOffStormKind();

    u32 mCount;
    u32 mStormCount;
    hel::math::Vector2 mBasePos;
    Config mConfig;
    bool mIsMoveStart;
    bool mIsStorm;
    bool mIsOn;
    u32 mOnOffIndex;
    u32 mOnCount;
    f32 mRotX;
};

}}}}  // namespace scn::step::boss::roah

#endif
