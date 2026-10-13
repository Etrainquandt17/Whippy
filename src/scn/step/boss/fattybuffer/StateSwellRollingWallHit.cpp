#include "scn/step/boss/fattybuffer/StateSwellRollingWallHit.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
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
#include "scn/step/boss/fattybuffer/StalactiteCtrl.h"
#include "scn/step/boss/fattybuffer/StateSwellRollingRebound.h"
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

StateSwellRollingWallHit::StateSwellRollingWallHit(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().fattybuffer();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x19);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_8);
    obj().move().resetSpeedH();
    hel::math::Vector2 pos(param._10C.x * obj().target().getSign(), param._10C.y);
    hel::math::Vector2 speed(param._114.x * -obj().target().getSign(), param._114.y);
    pos.scale(obj().model().getTotalScale().getXY());
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarPuff);
    hel::math::Vector3 effectPos = obj().model().model().nodes().at(2).worldTrans();
    obj().effect().state().requestPD(static_cast<effect::Kind>(0x13F), effectPos,
                                     obj().target().isRightDir() ? hel::math::Direction3::FRONT_TO_RIGHT : hel::math::Direction3::FRONT_TO_LEFT);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
    custom.stalactiteCtrl().fall();
}

StateSwellRollingWallHit::~StateSwellRollingWallHit() {}

void StateSwellRollingWallHit::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwellRollingRebound, Boss*>(objPtr());
    }
}

void StateSwellRollingWallHit::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellRollingWallHit::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
