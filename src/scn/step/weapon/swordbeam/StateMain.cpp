#include "scn/step/weapon/swordbeam/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/swordbeam/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace swordbeam {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().swordBeam();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x20));
    obj().objColl().addAttack(
        0, param._0, hel::math::Vector2(param._4 * obj().target().getSign(), param._8),
        hel::math::Vector2(param._C * obj().target().getSign(), param._10)
    );
    hel::math::Direction3 dir;
    dir.mFront = hel::math::Vector3::BASIS_X;
    dir.mFront *= obj().target().getSign();
    dir.restructFrontUp();
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x529), 0, dir);
}

void StateMain::procAnim() {
    if (++mFrame >= obj().param().swordBeam()._14) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().swordBeam();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airAccelFall(obj().target().isRightDir(), param._18, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide()) {
        obj().dead();
    } else if (obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    } else if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}
}
}
}
