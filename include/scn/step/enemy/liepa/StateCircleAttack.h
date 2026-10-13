#ifndef SCN_STEP_ENEMY_LIEPA_STATECIRCLEATTACK_H
#define SCN_STEP_ENEMY_LIEPA_STATECIRCLEATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace liepa {

class StateCircleAttack : public StateBase {
public:
    struct Config {
        u32 _0;
    };

    StateCircleAttack(Enemy* enemy, Config config);
    virtual ~StateCircleAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mShotFrame;
    hel::math::Vector2 mCenter;
    f32 mRadius;
    Config mConfig;
};

}}}}  // namespace scn::step::enemy::liepa

#endif
