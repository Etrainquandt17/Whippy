#include "scn/step/boss/hrd3/StatePressLanding.h"

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
namespace hrd3 {

StatePressLanding::StatePressLanding(Boss* boss) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHatedHero(obj());
    Utility::ControlHateOnAction(obj());
    u32 scriptKind = 0x15;
    if (custom.partsCtrl().isExistHipNeedle()) {
        scriptKind = 0x16;
    }
    obj().model().reqScript(scriptKind);
    reqStar();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressLanding::~StatePressLanding() {}

void StatePressLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePressLanding::procMove() {}

void StatePressLanding::procFixPos() {}

void StatePressLanding::reqStar() {
    const Param& param = obj().param().hrd3();
    hel::math::Vector2 pos = param._14;
    hel::math::Vector2 speed = param._24;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::hrd3
