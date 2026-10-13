#include "scn/step/weapon/ninjawaveshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjawaveshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjawaveshot {

namespace {

Param param(Weapon& weapon) {
    return weapon.param().ninjaWaveShot();
}

}

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mCount(0) {
    obj().setValidAttackRumble(true);
    obj().move().setSpeedH(obj().target().getSign() * param(obj())._0);
    obj().comp().permSoundSE().start(0x253);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    obj().objColl().clearAttack();
    if (mCount == 0) {
        hel::math::Vector3 pos = obj().location().pos();
        pos.y += param(obj())._10;
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x497), pos);
        setAttack();
    }
    if (++mCount > param(obj())._14) {
        mCount = 0;
    }
    if (++mFrame >= param(obj())._18) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(param(obj())._1C, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (!obj().objColl().attack().isCollide() && !obj().objColl().attack().isCollideGimmick() && obj().mapColl().isHit()) {
        if (hel::math::Math::Abs(obj().mapColl().normal().x) > 0.75f) {
            obj().dead();
        }
    }
}

void StateMain::setAttack() {
    obj().objColl().clearAttack();
    f32 x = obj().target().getSign();
    x *= param(obj())._4;
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xDC));
    obj().objColl().addAttack(0, param(obj())._C, hel::math::Vector2(x, 0.0f), hel::math::Vector2(x, param(obj())._8));
}

}}}}  // namespace scn::step::weapon::ninjawaveshot
