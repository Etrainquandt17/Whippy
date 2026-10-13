#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATEVORTEX_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATEVORTEX_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateVortex : public StateBase {
public:
    StateVortex(Enemy* enemy);
    virtual ~StateVortex();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mShakeFrame;
    hel::math::Vector3 mCenter;
    hel::math::Vector3 mOffset;
    hel::math::Vector3 mVelocity;
};

}}}}  // namespace scn::step::enemy::lowperbullet

#endif
