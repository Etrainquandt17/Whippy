#include "scn/step/boss/fattybuffer/StateStalactiteStart.h"

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
#include "scn/step/boss/fattybuffer/StateStalactiteJump.h"
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

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStalactiteStart::StateStalactiteStart(Boss* boss, StalactiteJumpKind kind) : StateBase(boss), mKind(kind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        obj().model().reqScript(0x23);
        break;
    case STALACTITE_JUMP_KIND_1:
        obj().model().reqScript(0x26);
        break;
    case STALACTITE_JUMP_KIND_2:
        obj().model().reqScript(0x29);
        break;
    case STALACTITE_JUMP_KIND_3:
        obj().model().reqScript(0x2C);
        break;
    case STALACTITE_JUMP_KIND_4:
        obj().model().reqScript(0x2F);
        break;
    }
    obj().guard().setType(static_cast<GuardType>(2));
}

StateStalactiteStart::~StateStalactiteStart() {}

void StateStalactiteStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateStalactiteJump, Boss*, StalactiteJumpKind>(objPtr(), mKind);
    }
}

void StateStalactiteStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStalactiteStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
