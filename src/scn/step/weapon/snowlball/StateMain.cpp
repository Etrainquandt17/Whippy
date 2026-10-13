#include "scn/step/weapon/snowlball/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace snowlball {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x307), 0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1A6));
    obj().objColl().addAttack(0, 0.25f);
    obj().objColl().addHit(0, 0.25f);
    obj().soundSE().start(0x2FA);
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().effect().normal().release();
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x308), obj().location().pos());
        obj().soundSE().stop();
        obj().comp().permSoundSE().start(0x2FB);
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().hit().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().objColl().attack().isCollide()) {
        obj().effect().normal().release();
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x308), obj().location().pos());
        obj().soundSE().stop();
        obj().comp().permSoundSE().start(0x2FB);
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::snowlball
