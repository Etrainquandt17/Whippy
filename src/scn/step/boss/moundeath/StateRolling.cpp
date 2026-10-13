#include "scn/step/boss/moundeath/StateRolling.h"

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
#include "scn/step/boss/moundeath/StateRollingEnd.h"
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

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateRolling::StateRolling(Boss* boss) : StateBase(boss), mCount(0), mRot(0.0f), mWait(0), mIsRight(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x18);
    obj().move().resetVelocity();
    obj().guard().setType(static_cast<GuardType>(6));
    custom.setBodyCollRolling();
    obj().soundSE().state().start(0x5A6);
    mRot = chara::ModelRotCtrl::ROT_H_TARGET;
}

StateRolling::~StateRolling() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateRolling::procAnim() {
    const Param& param = obj().param().moundeath();
    mCount++;
    f32 delta = static_cast<f32>(param._114) * (360.0f / static_cast<f32>(param._110));
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, delta);
    obj().model().rotCtrl().initRotH(mRot);
    if (mCount == param._110) {
        obj().stateChanger().setNextState<StateRollingEnd, Boss*>(objPtr());
    }
}

void StateRolling::procMove() {
    const Param& param = obj().param().moundeath();
    if (mWait != 0) {
        mWait--;
    }
    if (mWait == 0) {
        hel::math::Vector3 target = Utility::GetHatedHeroPos(obj());
        bool isRight = mIsRight;
        if (target.squareDistance(obj().location().pos()) > param._13C) {
            isRight = target.x > obj().location().pos().x;
        }
        if (isRight != mIsRight) {
            obj().soundSE().state().start(0x5A6);
        }
        mIsRight = isRight;
        obj().move().groundAccel(isRight, param._118);
    } else {
        obj().move().groundDecel(param._12C);
    }
}

void StateRolling::procFixPos() {
    if (common::StateFall::TryToChangeState(objPtr())) {
        return;
    }
    const Param& param = obj().param().moundeath();
    chara::MapCollResult result = obj().mapColl().result();
    if (mCount > 20 && (result.isHitWallFront() || obj().worldCage().isCorrected())) {
        mWait = param._128;
        f32 sign = obj().move().velocity().x > 0.0f ? 1.0f : -1.0f;
        hel::math::Vector2 offset(param._130 * sign, param._134);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xD8), obj().location().pos() + offset.toVector3());
        hel::math::Vector3 velocity = obj().move().velocity();
        velocity.x *= -param._124;
        obj().move().setVelocity(velocity);
        obj().soundSE().state().start(0x5A6);
    }
}

}}}}  // namespace scn::step::boss::moundeath
