#include "scn/step/boss/moundeath/StatePressJump.h"

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
#include "scn/step/boss/moundeath/StatePressFallStart.h"
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

StatePressJump::StatePressJump(Boss* boss, JumpKind kind)
    : StateBase(boss), mCount(0), mFrame(0), mRotNum(0), mStartPos(), mGoalPos(), mRot(0.0f), mRotDiff(0.0f), mKind(kind) {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    mStartPos = obj().location().pos().getXY();
    mGoalPos = mStartPos;
    switch (mKind) {
    case JUMP_KIND_0:
        obj().model().reqScript(0xA);
        mGoalPos.x += param._78 * obj().target().getSign();
        mGoalPos.y += param._7C;
        mFrame = param._74;
        mRotNum = param._80;
        break;
    case JUMP_KIND_1:
        obj().model().reqScript(0xD);
        mGoalPos.x = Utility::GetHatedHeroPos(obj()).x;
        mGoalPos.y += param._94;
        mFrame = param._90;
        mRotNum = param._98;
        break;
    case JUMP_KIND_2:
        obj().model().reqScript(0xD);
        mGoalPos.x = Utility::GetHatedHeroPos(obj()).x;
        if (hel::math::Math::AbsF32(mGoalPos.x - obj().comp().mainCamera().getCenter().x) > param._B0) {
            mGoalPos.x = mGoalPos.x > obj().comp().mainCamera().getCenter().x ? param._B0 + obj().comp().mainCamera().getCenter().x
                                                                             : obj().comp().mainCamera().getCenter().x - param._B0;
        }
        mGoalPos.y += param._AC;
        mFrame = param._A8;
        mRotNum = param._B4;
        break;
    default:
        mFrame = param._74;
        break;
    }
    obj().target().setIsRightDir(mGoalPos.x > obj().location().pos().x);
    mRot = obj().model().rotCtrl().getRotH() * obj().target().getSign();
    mRotDiff = chara::ModelRotCtrl::ROT_H_TARGET - mRot;
}

StatePressJump::~StatePressJump() {}

void StatePressJump::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePressFallStart, Boss*, JumpKind>(objPtr(), mKind);
        return;
    }
    f32 delta = (360.0f * static_cast<f32>(mRotNum) + mRotDiff) / static_cast<f32>(mFrame);
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, delta);
    obj().model().rotCtrl().initRotH(mRot);
}

void StatePressJump::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector2 pos = hel::math::Vector2::ZERO;
    pos.x = hel::math::Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, mGoalPos.y, hel::math::Math::SinDegF(90.0f * t));
    obj().location().setPos(pos.toVector3());
}

void StatePressJump::procFixPos() {}

}
}
}
}
