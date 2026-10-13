#include "scn/step/boss/roah/Custom.h"

#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateDamageL.h"
#include "scn/step/boss/roah/StateDead.h"
#include "scn/step/boss/roah/StateFirst.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCollisionCtrl(boss), mWeaponCtrl(boss), mRotCtrl(boss), mMahoroaCtrl(boss), mStormCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().roah();
    obj().hitPoint().init(Utility::IsVariationExtra(obj()) ? param.mHitPointExtra : param.mHitPoint);
    obj().angry().setAngryHpRate(Utility::IsVariationExtra(obj()) ? param.mAngryHpRateExtra : param.mAngryHpRate);
    obj().handicap().setup();
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.Roah.Brain.ExecEx");
        obj().angry().setChangeBrain("Scn.Step.Boss.Roah.Brain.ExecAngryEx");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.Roah.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Roah.Brain.ExecAngry");
    }
    obj().mapColl().setValid(false);
    setSubAnimTexture();
    setSubAnimOar();
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onStart() {
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
}

void Custom::onDamage() {}

void Custom::onDead() {
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onProcAnim() {
    mRotCtrl.update();
    mStormCtrl.update();
}

void Custom::onProcMove() {
    mMahoroaCtrl.update();
}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
    mWeaponCtrl.update();
    mCollisionCtrl.update();
}

CollisionCtrl& Custom::collisionCtrl() {
    return mCollisionCtrl;
}

WeaponCtrl& Custom::weaponCtrl() {
    return mWeaponCtrl;
}

RotCtrl& Custom::rotCtrl() {
    return mRotCtrl;
}

MahoroaCtrl& Custom::mahoroaCtrl() {
    return mMahoroaCtrl;
}

StormCtrl& Custom::stormCtrl() {
    return mStormCtrl;
}

void Custom::setSubAnimTexture() {
    obj().model().anim().subAnimSet(0, 2, 0);
    obj().model().anim().subAnimAccessor(0).start(true);
}

void Custom::setSubAnimOar() {
    obj().model().anim().subAnimSet(1, 3, 0xC);
    obj().model().anim().subAnimAccessor(1).start(true);
}

void Custom::resetSubAnimOar() {
    obj().model().anim().subAnimClear(1);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
