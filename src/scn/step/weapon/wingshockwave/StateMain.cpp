#include "scn/step/weapon/wingshockwave/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/wingshockwave/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace wingshockwave {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mEffectScale(1.0f), mIsEffectRequested(false) {
    const Param& param = obj().param().wingShockWave();
    ocoll::AttackType attackType = static_cast<ocoll::AttackType>(0xD0);
    f32 radius = param._C;
    f32 length = param._10 - radius;
    mEffectScale = param._18;
    if (obj().variation() == 1) {
        attackType = static_cast<ocoll::AttackType>(0xD1);
        radius = param._1C;
        length = param._20 - radius;
        mEffectScale = param._28;
    }
    obj().objColl().setAttackType(attackType);
    obj().objColl().addAttack(0, radius, hel::math::Vector2(0.0f, 0.3f), hel::math::Vector2(0.0f, length));
    obj().setValidAttackRumble(true);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (!mIsEffectRequested) {
        const Param& param = obj().param().wingShockWave();
        obj().effect().normal().requestN(
            static_cast<effect::Kind>(0x59D), 0, hel::math::Vector3(0.0f, -0.2f, obj().variation() == 1 ? param._24 : param._14), mEffectScale
        );
        mIsEffectRequested = true;
    }
    if (++mFrame >= obj().param().wingShockWave()._4) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(obj().param().wingShockWave()._0, fall);
}

void StateMain::procFixPos() {
    if (obj().mapColl().result().isDead()) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (!obj().objColl().attack().isCollide() && !obj().objColl().attack().isCollideGimmick() && obj().mapColl().isHit()) {
        if (hel::math::Math::Abs(obj().mapColl().normal().x) > 0.75f) {
            obj().dead();
        }
    }
}

}
}
}
}
