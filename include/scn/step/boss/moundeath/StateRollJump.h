#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEROLLJUMP_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEROLLJUMP_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateRollJump : public StateBase {
public:
    struct Config {
        bool _0;
    };

    StateRollJump(Boss* boss, Config config);
    virtual ~StateRollJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector2 mStartPos;
    f32 mDistance;
};

}}}}  // namespace scn::step::boss::moundeath

#endif
