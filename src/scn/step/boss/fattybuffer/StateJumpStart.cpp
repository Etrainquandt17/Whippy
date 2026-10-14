#include "scn/step/boss/fattybuffer/StateJumpStart.h"

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
#include "scn/step/boss/fattybuffer/StateJump.h"
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

StateJumpStart::StateJumpStart(Boss* boss, f32 speedH, f32 speedV) : StateBase(boss), mSpeedH(speedH), mSpeedV(speedV) {
    obj().footState().setGround();
    obj().model().reqScript(8);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJump, Boss*, f32, f32>(objPtr(), mSpeedH, mSpeedV);
    }
}

void StateJumpStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
