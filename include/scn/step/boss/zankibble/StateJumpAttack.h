#ifndef SCN_STEP_BOSS_ZANKIBBLE_STATEJUMPATTACK_H
#define SCN_STEP_BOSS_ZANKIBBLE_STATEJUMPATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class StateJumpAttack : public StateBase {
public:
    struct Config {
        bool _0;
    };

    StateJumpAttack(Boss* boss, Config config);
    virtual ~StateJumpAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqCutterSlant();

    bool mIsFall;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mTargetPos;
};

class StateJumpAttackStart : public StateBase {
public:
    StateJumpAttackStart(Boss* boss, StateJumpAttack::Config config);
    virtual ~StateJumpAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateJumpAttack::Config mConfig;
};

}}}}  // namespace scn::step::boss::zankibble

#endif
