#ifndef SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLTHROW_H
#define SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLTHROW_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateEnergyBallThrow : public StateBase {
public:
    StateEnergyBallThrow(Boss* boss, util::ObjRefHandle<weapon::Weapon> ball, u32 time, f32 speed);
    virtual ~StateEnergyBallThrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mSpeed;
    util::ObjRefHandle<weapon::Weapon> mBall;
};

}}}}  // namespace scn::step::boss::goliath

#endif
