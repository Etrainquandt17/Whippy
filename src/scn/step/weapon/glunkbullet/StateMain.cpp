#include "scn/step/weapon/glunkbullet/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace glunkbullet {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mStartPos() {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19B));
    obj().objColl().addAttack(0, 0.25f);
    obj().objColl().addHit(0, 0.25f);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x1AB), 0);
    mStartPos = obj().location().pos().getXY();
    obj().move().setVelocity(obj().move().velocity() * 0.07f);
}

void StateMain::procAnim() {
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(0.75f);
    } else {
        obj().move().resetMoveRate();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
    if ((mStartPos - obj().location().pos().getXY()).squareLength() > 9.0f) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x1AC), 0);
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().mapColl().isHit() || obj().objColl().hit().isCollide()) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x1AC), 0);
        obj().dead();
    }
}

}
}
}
}
