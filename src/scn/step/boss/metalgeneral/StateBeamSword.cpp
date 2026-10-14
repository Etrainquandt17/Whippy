#include "scn/step/boss/metalgeneral/StateBeamSword.h"

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
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/ScriptKind.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
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
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateBeamSword::StateBeamSword(Boss* boss, u32 scriptKind) : StateBase(boss), mScriptKind(scriptKind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(mScriptKind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    Utility::ControlHateOnAction(obj());
}

StateBeamSword::~StateBeamSword() {
    obj().objColl().clearAttack(1);
}

void StateBeamSword::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        Vector2 pos(param._F8.x * obj().target().getSign(), param._F8.y);
        Vector2 speed(param._100.x * obj().target().getSign(), param._100.y);
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3());
    }
    if (obj().scriptTrigger().get(1)) {
        f32 speed = param._EC * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    if (obj().scriptTrigger().get(2)) {
        f32 speed = param._F4 * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    if (obj().scriptTrigger().get(3)) {
        obj().gearManager().gear(0).setVisibility(true);
    }
    if (obj().scriptTrigger().get(4)) {
        obj().gearManager().gear(0).setVisibility(false);
    }
    if (obj().scriptTrigger().get(5)) {
        f32 speed = param._F0 * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
}

void StateBeamSword::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().groundDecel(param._1C);
}

void StateBeamSword::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
