#ifndef SCN_STEP_BOSS_ZANKIBBLE_STATEATTACK_H
#define SCN_STEP_BOSS_ZANKIBBLE_STATEATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/zankibble/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class StateAttack : public StateBase {
public:
    struct Config {
        ScriptKind _0;
        hel::math::Vector2 _4;
        bool _C;
    };

    StateAttack(Boss* boss, Config config);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqCutterStraight();
    void reqCutterCircle();
    void reqCutterBackCircle();

    Config mConfig;
    bool mIsScaling;
    u32 mCount;
};

}
}
}
}

#endif
