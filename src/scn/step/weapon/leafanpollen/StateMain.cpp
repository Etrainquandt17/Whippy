#include "scn/step/weapon/leafanpollen/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/leafanpollen/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace leafanpollen {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0.0f) {
    const Param& param = obj().param().leafanPollen();
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += param._4;
    obj().location().setPos(pos);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19B));
    obj().objColl().addAttack(0, param._8, hel::math::Vector2(0.0f, 0.0f), hel::math::Vector2(0.0f, 0.0f));
    obj().objColl().addHit(0, param._C);
    obj().move().resetSpeedH();
    obj().move().setSpeedV(param._0);
    obj().soundSE().start(0x2E8);
}

void StateMain::procAnim() {
    const Param& param = obj().param().leafanPollen();
    _C += 6.0f;
    switch (obj().variation()) {
    case 0:
        obj().move().setSpeedH(param._14);
        obj().model().rotCtrl().setRotH(_C);
        obj().model().rotCtrl().setRotV(_C);
        break;
    case 1:
        obj().move().setSpeedH(param._18);
        obj().model().rotCtrl().setRotH(-_C);
        obj().model().rotCtrl().setRotV(-_C);
        break;
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().leafanPollen();
    _8++;
    switch (obj().variation()) {
    case 0:
        obj().move().setSpeedH(param._14);
        break;
    case 1:
        obj().move().setSpeedH(param._18);
        break;
    }
    if (_8 > param._1C) {
        obj().move().airDecelFall(param._30, param._34);
    } else {
        obj().move().airDecelFall(param._20, param._24);
    }
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().comp().permEffect().normal().requestPD(static_cast<effect::Kind>(0x124), obj().location().pos(), hel::math::Direction3::BASIS);
        obj().soundSE().stop();
        obj().comp().permSoundSE().start(0x2B1);
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().objColl().hit().isCollide()) {
        obj().comp().permEffect().normal().requestPD(static_cast<effect::Kind>(0x124), obj().location().pos(), hel::math::Direction3::BASIS);
        obj().soundSE().stop();
        obj().comp().permSoundSE().start(0x2B1);
        obj().dead();
    }
}

}
}
}
}
