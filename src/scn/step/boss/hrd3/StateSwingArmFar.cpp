#include "scn/step/boss/hrd3/StateSwingArmFar.h"

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
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/boss/hrd3/StateWaitFar.h"
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

StateSwingArmFar::StateSwingArmFar(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(boss->location().pos()), mGoalPos(), mIsMove(false) {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos.x = param._128 + (custom.landCtrl().getCenterX() + 0.5f * -custom.landCtrl().getWidth());
    mStartPos.y = param._130 + custom.landCtrl().getFloorY();
    mStartPos.z = param._134;
    mGoalPos = mStartPos;
    mGoalPos.x = param._12C + (custom.landCtrl().getCenterX() + 0.5f * custom.landCtrl().getWidth());
    obj().model().reqScript(0x22);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateSwingArmFar::~StateSwingArmFar() {}

void StateSwingArmFar::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (mIsMove && mCount < mFrame) {
        mCount++;
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateSwingArmFar::procMove() {
    const Param& param = obj().param().hrd3();
    if (mIsMove) {
        f32 depthRate;
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
        f32 sin = hel::math::Math::SinDegF(180.0f * t);
        depthRate = 1.0f - (1.0f - sin) * (1.0f - sin);
        hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
        pos.z = hel::math::Math::LinearInterpolation(mGoalPos.z, param._138, depthRate);
        obj().location().setPos(pos);
    } else {
        obj().location().setPos(hel::math::Math::LinearInterpolation(obj().location().pos(), mStartPos, 0.05f));
    }
}

void StateSwingArmFar::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
