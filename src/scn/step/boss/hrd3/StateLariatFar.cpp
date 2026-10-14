#include "scn/step/boss/hrd3/StateLariatFar.h"

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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateLariatFar::StateLariatFar(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mRot(0.0f), mRotSpeed(0.0f), mPhase(PHASE_0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHatedHero(obj());
    obj().model().reqScript(0x19);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateLariatFar::~StateLariatFar() {}

void StateLariatFar::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (mPhase) {
    case PHASE_0:
        if (obj().scriptTrigger().get(0)) {
            mRot = obj().model().rotCtrl().getRotH() * obj().target().getSign();
            custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
            obj().soundSE().state().start(0x3C9);
            mPhase = PHASE_1;
        }
        break;
    case PHASE_1:
        updateRotate();
        mCount++;
        if (mCount >= mFrame) {
            obj().model().reqScript(0x1A);
            mPhase = PHASE_2;
        }
        break;
    case PHASE_2:
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
        }
        break;
    }
}

void StateLariatFar::procMove() {}

void StateLariatFar::procFixPos() {}

void StateLariatFar::updateRotate() {
    const Param& param = obj().param().hrd3();
    mRotSpeed += param._C4;
    mRotSpeed = Math::Limit(mRotSpeed, param._C0);
    mRot += mRotSpeed;
    if (mRot < -180.0f) {
        mRot += 360.0f;
    }
    if (mRot > 180.0f) {
        mRot -= 360.0f;
    }
    obj().model().rotCtrl().initRotH(mRot);
}

}}}}  // namespace scn::step::boss::hrd3
