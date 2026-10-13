#include "scn/step/weapon/watergalboroswater/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/watergalboroswater/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace watergalboroswater {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().waterGalborosWater();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1B1));
    obj().objColl().addAttack(0, param._0);
    obj().objColl().addHit(0, param._0);
    obj().objColl().hit().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x57C), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    const Param& param = obj().param().waterGalborosWater();
    mFrame++;
    if (mFrame == param._4) {
        obj().objColl().hit().setValid(true);
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().waterGalborosWater();
    obj().move().airDecelFall(param._8, param._C);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().hit().isCollide() || obj().objColl().attack().isCollide()) {
        dead();
    }
}

void StateMain::dead() {
    if (!obj().isDead()) {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x578), obj().location().pos());
        obj().comp().permSoundSE().start(0x585);
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::watergalboroswater
