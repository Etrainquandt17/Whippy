#include "scn/step/boss/fattybuffer/StateStalactiteJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
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
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateStalactiteLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStalactiteJump::StateStalactiteJump(Boss* boss, StalactiteJumpKind kind) : StateBase(boss), mKind(kind) {
    const Param& param = obj().param().fattybuffer();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        obj().model().reqScript(0x24);
        obj().move().setSpeedV(param._13C);
        break;
    case STALACTITE_JUMP_KIND_1:
        obj().model().reqScript(0x27);
        obj().move().setSpeedV(param._14C);
        break;
    case STALACTITE_JUMP_KIND_2:
        obj().model().reqScript(0x2A);
        obj().move().setSpeedV(param._15C);
        break;
    case STALACTITE_JUMP_KIND_3:
        obj().model().reqScript(0x2D);
        obj().move().setSpeedV(param._13C);
        break;
    case STALACTITE_JUMP_KIND_4:
        obj().model().reqScript(0x30);
        obj().move().setSpeedV(param._15C);
        break;
    }
    obj().guard().setType(static_cast<GuardType>(2));
}

StateStalactiteJump::~StateStalactiteJump() {}

void StateStalactiteJump::procAnim() {}

void StateStalactiteJump::procMove() {
    const Param& param = obj().param().fattybuffer();
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        fall = param._140;
        break;
    case STALACTITE_JUMP_KIND_1:
        fall = param._150;
        break;
    case STALACTITE_JUMP_KIND_2:
        fall = param._160;
        break;
    case STALACTITE_JUMP_KIND_3:
        fall = param._140;
        break;
    case STALACTITE_JUMP_KIND_4:
        fall = param._160;
        break;
    }
    obj().move().airDecelFall(param._18, fall);
}

void StateStalactiteJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateStalactiteLanding, Boss*, StalactiteJumpKind>(objPtr(), mKind);
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
