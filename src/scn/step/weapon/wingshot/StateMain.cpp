#include "scn/step/weapon/wingshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/wingshot/Param.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace wingshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mRotV(0.0f) {
    obj().model().reqScript(0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xCE));
    obj().objColl().setAttackCenter(0, Vector2::ZERO);
    obj().objColl().addAttack(
        0, obj().param().wingShot()._0, Vector2(obj().target().getSign() * (obj().param().wingShot()._4 - 0.2f), 0.0f),
        Vector2(-1.0f * obj().target().getSign() * obj().param().wingShot()._4, 0.0f)
    );
    Vector3 velocity = obj().move().velocity();
    mRotV = 90.0f + -Math::Atan2DegF(velocity.x, velocity.y);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    mFrame++;
    obj().model().rotCtrl().setRotH(85.0f * obj().target().getSign());
    obj().model().rotCtrl().setRotV(mRotV);
    if (mFrame > obj().param().wingShot()._8) {
        obj().dead();
    } else if (obj().water().isInWater()) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().wingShot();
    obj().move().decel(param._C);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::wingshot
