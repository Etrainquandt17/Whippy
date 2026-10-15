#ifndef SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLCHARGE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateEnergyBallCharge : public StateBase {
public:
    StateEnergyBallCharge(Boss* boss, u32 _1, u32 _2, f32 _3);
    virtual ~StateEnergyBallCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqWeapon();
    void updateMotion();

    u32 mFrame;
    u32 mTime;
    u32 mThrowTime;
    f32 mThrowSpeed;
    hel::math::Vector3 mStartPos;
    util::ObjRefHandle<weapon::Weapon> mWeapon;
    u32 mShakeWait;
};

}}}}  // namespace scn::step::boss::goliath

#endif
