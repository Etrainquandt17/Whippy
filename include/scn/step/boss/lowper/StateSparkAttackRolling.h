#ifndef SCN_STEP_BOSS_LOWPER_STATESPARKATTACKROLLING_H
#define SCN_STEP_BOSS_LOWPER_STATESPARKATTACKROLLING_H

#include "hel/common/Array.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSparkAttackRolling : public StateBase {
public:
    StateSparkAttackRolling(Boss* boss, u32 frame);
    virtual ~StateSparkAttackRolling();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setAttack();
    void reqWeapon();
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRot;
    hel::common::Array<util::ObjRefHandle<weapon::Weapon>, 8> mWeapons;
};

}
}
}
}

#endif
