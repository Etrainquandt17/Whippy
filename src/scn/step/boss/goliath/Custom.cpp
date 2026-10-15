#include "scn/step/boss/goliath/Custom.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/StateCallback.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateDamageL.h"
#include "scn/step/boss/goliath/StateDeadSmash.h"
#include "scn/step/boss/goliath/StateFirst.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
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
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Enemy.h"
#include "util/ObjList.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCollisionCtrl(boss), mElevationCtrl(boss), mEnemyCtrl(boss), mIcicleCtrl(boss), mHairCtrl(boss), mEyeCtrl(boss),
      mLandCtrl(boss), mCameraCtrl(boss), mPunchCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().goliath();
    obj().hitPoint().init(Utility::IsVariationExtra(obj()) ? param._4 : param._0);
    obj().angry().setAngryHpRate(Utility::IsVariationExtra(obj()) ? param._C : param._8);
    obj().handicap().setup();
    obj().target().setIsRightDir(false);
    obj().shadow().changeDiameter(2.0f);
    obj().shadow().changeMaxHeight(12.0f);
    obj().shadow().setVisibility(true);
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.Goliath.Brain.BrainEx.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Goliath.Brain.BrainAngryEx.Exec");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.Goliath.Brain.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Goliath.Brain.BrainAngry.Exec");
    }
    obj().stateCallback().setCanClearAttack(false);
    obj().worldCage().changePadding(1.75f, 3.5f);
    mCameraCtrl.init();
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
}

void Custom::onDead() {
    obj().stateChanger().setNextState<StateDeadSmash, Boss*>(objPtr());
}

void Custom::onStateChange() {
    mCollisionCtrl.onStateChange();
}

void Custom::onProcAnim() {
    mElevationCtrl.update();
    mPunchCtrl.update();
    mHairCtrl.update();
    mEyeCtrl.update();
}

void Custom::onProcMove() {
    mCameraCtrl.update();
}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
}

CollisionCtrl& Custom::collisionCtrl() {
    return mCollisionCtrl;
}

ElevationCtrl& Custom::elevationCtrl() {
    return mElevationCtrl;
}

EnemyCtrl& Custom::enemyCtrl() {
    return mEnemyCtrl;
}

IcicleCtrl& Custom::icicleCtrl() {
    return mIcicleCtrl;
}

HairCtrl& Custom::hairCtrl() {
    return mHairCtrl;
}

EyeCtrl& Custom::eyeCtrl() {
    return mEyeCtrl;
}

LandCtrl& Custom::landCtrl() {
    return mLandCtrl;
}

CameraCtrl& Custom::cameraCtrl() {
    return mCameraCtrl;
}

PunchCtrl& Custom::punchCtrl() {
    return mPunchCtrl;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::goliath

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
