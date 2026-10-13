#ifndef SCN_STEP_ENEMY_CHASEKEYDEGOUT_STATECHASE_H
#define SCN_STEP_ENEMY_CHASEKEYDEGOUT_STATECHASE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace chasekeydegout {

class StateChase : public StateBase {
public:
    StateChase(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
    hel::math::Vector3 mAccel;
    f32 mSpeedMax;
    u32 mChaseFrame;
};

}}}}  // namespace scn::step::enemy::chasekeydegout

#endif
