#ifndef SCN_STEP_ENEMY_LIEPA_STATEMOVEATTACK_H
#define SCN_STEP_ENEMY_LIEPA_STATEMOVEATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace liepa {

class StateMoveAttack : public StateBase {
public:
    struct Config {
        f32 _0;
    };

    StateMoveAttack(Enemy* enemy, Config config);
    virtual ~StateMoveAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mTotalFrame;
    u32 mShotFrame;
    hel::math::Vector3 mVelocity;
    bool mIsMove;
    Config mConfig;
};

}}}}  // namespace scn::step::enemy::liepa

#endif
