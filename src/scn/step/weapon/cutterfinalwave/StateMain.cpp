#include "scn/step/weapon/cutterfinalwave/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/cutterfinalwave/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace cutterfinalwave {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().cutterFinalWave();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x37));
    obj().objColl().addAttack(0, param._0, hel::math::Vector2(param._4, param._8), hel::math::Vector2(param._C, param._10));
    obj().effect().normal().requestND(static_cast<effect::Kind>(0xCD), 0, obj().target().getDirection3());
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    _8++;
    if (_8 == obj().param().cutterFinalWave()._14) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(obj().param().cutterFinalWave()._18, fall);
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
