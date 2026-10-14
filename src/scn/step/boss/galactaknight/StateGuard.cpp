#include "scn/step/boss/galactaknight/StateGuard.h"

#include "app/Random.h"
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
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardFlash.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateGuard::StateGuard(Boss* boss, f32 distance, u32 frame, u32 guardFrame)
    : StateBase(boss), mFrame(frame), mCount(0), mGuardFrame(guardFrame), mStartPos(boss->location().pos()), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = distance * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    obj().model().reqScript(0xC);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().flash().guard().setIsValid(true);
    obj().guard().setType(static_cast<GuardType>(6));
}

StateGuard::~StateGuard() {
    obj().flash().guard().setIsValid(false);
}

void StateGuard::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    }
    if (mGuardFrame != 0) {
        mGuardFrame--;
        if (mGuardFrame == 0) {
            obj().model().reqScript(0xD);
            obj().flash().guard().setIsValid(false);
            obj().guard().setType(static_cast<GuardType>(0));
            DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_1);
        }
    }
    if (mGuardFrame == 0 && obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateGuard::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StateGuard::procFixPos() {}

void StateGuard::procObjCollReact() {
    if (mGuardFrame != 0 && obj().objColl().bodyColl().hit().isCollide()) {
        obj().soundSE().normal().start(0x396);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xDD), obj().location().pos());
    }
}

}}}}  // namespace scn::step::boss::galactaknight
