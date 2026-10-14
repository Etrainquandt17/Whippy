#include "scn/step/boss/hrd3pilot/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3pilot/StateMissile.h"
#include "scn/step/boss/hrd3pilot/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

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
