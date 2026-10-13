#include "scn/step/boss/hrd3/StatePressBound.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/InfoHitPointCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/PilotCtrl.h"
#include "scn/step/boss/hrd3/ShadowCtrl.h"
#include "scn/step/boss/hrd3/StatePressLanding.h"
#include "scn/step/boss/hrd3/StateWait.h"
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
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePressBound::StatePressBound(Boss* boss, u32 frame) : StateBase(boss), mCount(0), mFrame(frame), mIsLast(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHatedHero(obj());
    setTargetPos();
    u32 scriptKind = 0x13;
    if (custom.partsCtrl().isExistHipNeedle()) {
        scriptKind = 0x14;
    }
    obj().model().reqScript(scriptKind);
    reqBoundEffect();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressBound::~StatePressBound() {}

void StatePressBound::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else if (mIsLast) {
        obj().stateChanger().setNextState<StatePressLanding, Boss*>(objPtr());
    } else {
        mCount = 0;
        setTargetPos();
        reqBoundEffect();
    }
}

void StatePressBound::procMove() {
    const Param& param = obj().param().hrd3();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 sin = hel::math::Math::SinDegF(180.0f * t);
    f32 easeOut = 1.0f - (1.0f - sin) * (1.0f - sin);
    f32 height = hel::math::Math::LinearInterpolation(sin, easeOut, 0.8f);
    hel::math::Vector3 pos = mStartPos;
    pos.x = hel::math::Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y += hel::math::Math::LinearInterpolation(0.0f, param._B0, height);
    obj().location().setPos(pos);
}

void StatePressBound::procFixPos() {}

void StatePressBound::setTargetPos() {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos = obj().location().pos();
    mGoalPos = mStartPos;
    mGoalPos.x += param._AC * obj().target().getSign();
    f32 x = custom.landCtrl().getAdjustX(mGoalPos.x, param._C);
    if (x != mGoalPos.x) {
        mGoalPos.x = x;
        mIsLast = true;
    }
}

void StatePressBound::reqBoundEffect() {
    const Param& param = obj().param().hrd3();
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x2EF), obj().location().pos());
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().soundSE().normal().start(0x3CF);
    hel::math::Vector2 pos = param._14;
    hel::math::Vector2 speed = param._24;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}
}
}
}
