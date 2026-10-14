#include "scn/step/weapon/owgulffeather/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace owgulffeather {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    f32 angle = Math::Abs(Math::Atan2DegF(obj().move().velocity().x, -obj().move().velocity().y));
    obj().model().setCustomMtx(
        Matrix34::CreateRotAxisDeg(Vector3(0.0f, 0.0f, obj().target().getSign()), angle - 90.0f)
    );
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x5A4), 0);
    if (obj().variation() == 0) {
        addObjColl();
    } else {
        obj().setVisibility(false);
    }
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    mFrame++;
    if (obj().variation() == 1 && mFrame == 7) {
        obj().setVisibility(true);
        addObjColl();
    }
    if (mFrame >= 120) {
        dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().objColl().hit().isCollide() ||
        obj().mapColl().isHit()) {
        dead();
    }
}

void StateMain::dead() {
    obj().dead();
}

void StateMain::addObjColl() {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19F));
    obj().objColl().addAttack(0, 0.1f);
    obj().objColl().addHit(0, 0.1f);
}

}}}}  // namespace scn::step::weapon::owgulffeather
