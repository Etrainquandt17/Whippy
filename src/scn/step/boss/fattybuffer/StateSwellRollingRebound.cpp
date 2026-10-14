#include "scn/step/boss/fattybuffer/StateSwellRollingRebound.h"

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
#include "scn/step/boss/fattybuffer/StateSwellRollingLanding.h"
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
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellRollingRebound::StateSwellRollingRebound(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().target().invert();
    obj().model().rotCtrl().setRotHIntoTarget();
    obj().model().reqScript(0x1A);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_4);
    const Param& param = obj().param().fattybuffer();
    obj().move().setVelocity(Vector3(param._104 * obj().target().getSign(), param._108, 0.0f));
}

StateSwellRollingRebound::~StateSwellRollingRebound() {}

void StateSwellRollingRebound::procAnim() {}

void StateSwellRollingRebound::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().airDecelFall(param._18, param._1C);
}

void StateSwellRollingRebound::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateSwellRollingLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
