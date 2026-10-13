#include "scn/step/weapon/ninjadasheffect/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjadasheffect/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjadasheffect {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mWait(0), mFrame(0), mIsEnd(false) {
    const Param& param = obj().param().ninjaDashEffect();
    obj().move().resetVelocity();
    obj().model().rotCtrl().setValid(false);
    obj().setValidAttackRumble(true);
    if (obj().variation() == 1) {
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x496), 0, obj().target().getDirection3(), hel::math::Vector3::BASIS_Y * param._14);
    }
    switch (obj().variation()) {
    case 0:
        mWait = 5;
        break;
    case 1:
        mWait = 3;
        break;
    case 2:
        mWait = 1;
        break;
    default:
        mWait = 1;
        break;
    }
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (mIsEnd) {
        obj().dead();
        return;
    }
    if (mWait > 0) {
        mWait--;
        if (mWait == 0) {
            const Param& param = obj().param().ninjaDashEffect();
            f32 sign = obj().target().getSign();
            obj().objColl().setAttackCenter(0, hel::math::Vector2(sign * param._8, param._14));
            obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xDD));
            obj().objColl().addAttack(0, param._4, hel::math::Vector2(sign * param._C, param._14), hel::math::Vector2(sign * param._10, param._14));
        }
    } else {
        mFrame++;
        if (mFrame > obj().param().ninjaDashEffect()._0) {
            mIsEnd = true;
            obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xDE));
            obj().objColl().renewAttack();
        }
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

}
}
}
}
