#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATESTILL_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATESTILL_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateStill : public StateBase {
public:
    StateStill(Enemy* enemy);
    virtual ~StateStill();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mEndFrame;
    u32 mShakeFrame;
    hel::math::Vector3 mBasePos;
};

}}}}  // namespace scn::step::enemy::lowperbullet

#endif
