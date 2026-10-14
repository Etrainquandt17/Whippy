#include "scn/step/boss/moundeath/StateRollingStart.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
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
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/StateRolling.h"
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

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateRollingStart::StateRollingStart(Boss* boss) : StateBase(boss), mCount(0), mRot(0.0f), mRotDiff(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x18);
    Utility::ControlHateOnAction(obj());
    Utility::TurnHatedHero(obj());
    obj().guard().setType(static_cast<GuardType>(6));
    custom.setBodyCollRolling();
    mRot = obj().model().rotCtrl().getRotH() * obj().target().getSign();
    mRotDiff = chara::ModelRotCtrl::ROT_H_TARGET - mRot;
    obj().soundSE().normal().start(0x5A6);
}

StateRollingStart::~StateRollingStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateRollingStart::procAnim() {
    const Param& param = obj().param().moundeath();
    mCount++;
    f32 delta = (360.0f * static_cast<f32>(param._100) + mRotDiff) / static_cast<f32>(param._FC);
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, delta);
    obj().model().rotCtrl().initRotH(mRot);
    if (mCount == param._FC) {
        obj().stateChanger().setNextState<StateRolling, Boss*>(objPtr());
    }
}

void StateRollingStart::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().groundAccel(!obj().target().isRightDir(), param._104);
}

void StateRollingStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::moundeath
