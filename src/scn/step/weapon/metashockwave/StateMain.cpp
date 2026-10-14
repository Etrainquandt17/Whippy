#include "scn/step/weapon/metashockwave/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metashockwave/Param.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace metashockwave {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), _C(obj().param().metaShockWave()._8) {
    const Param& param = obj().param().metaShockWave();
    f32 radius = param._C;
    f32 length = param._10 - radius;
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x135));
    obj().objColl().addAttack(0, radius, Vector2(0.0f, 0.3f), Vector2(0.0f, length));
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x44C), 0, obj().target().getDirection3(), Vector3(0.0f, -0.2f, param._14));
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (++mFrame >= obj().param().metaShockWave()._4) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(obj().param().metaShockWave()._0, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (!obj().objColl().attack().isCollide() && !obj().objColl().attack().isCollideGimmick() && obj().mapColl().isHit()) {
        if (Math::Abs(obj().mapColl().normal().x) > 0.75f) {
            obj().dead();
        }
    }
}

}}}}  // namespace scn::step::weapon::metashockwave
