#include "scn/step/boss/hrd3pilot/Custom.h"

#include "gobj/GearModel.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/hrd3pilot/StateMissile.h"
#include "scn/step/boss/hrd3pilot/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

Custom::Custom(Boss& boss) : CustomBase(boss), mTailCtrl(boss) {}

void Custom::onInit() {
    obj().hitPoint().init(1);
    obj().objColl().bodyColl().clear();
    obj().mapColl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x459), 5);
    obj().model().rotCtrl().setRotHTargetDefault(0.0f);
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {}

void Custom::onDead() {}

void Custom::onProcAnim() {
    mTailCtrl.update();
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
}

void Custom::onProcMove() {}

void Custom::onProcFixPos() {}

void Custom::onProcObjCollReact() {}

void Custom::reqMotionMissileFar() {
    obj().model().reqScript(5);
}

void Custom::setNextStateMissile() {
    obj().stateChanger().setNextState<StateMissile, Boss*>(objPtr());
}

Vector3 Custom::getMissileLaunchPos() {
    return obj().model().model().nodes().at(4).worldTrans();
}

TailCtrl& Custom::tailCtrl() {
    return mTailCtrl;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::hrd3pilot

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
