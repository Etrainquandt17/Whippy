#include "scn/step/boss/hrd3/StatePunch.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/InfoHitPointCtrl.h"
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
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePunch::StatePunch(Boss* boss, bool isStrong) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    u32 scriptKind;
    if (obj().target().isRightDir()) {
        if (isStrong) {
            scriptKind = 0xB;
        } else {
            scriptKind = 9;
        }
    } else {
        if (isStrong) {
            scriptKind = 0xC;
        } else {
            scriptKind = 0xA;
        }
    }
    obj().model().reqScript(scriptKind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePunch::~StatePunch() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).partsCtrl().shrinkDrillForce();
}

void StatePunch::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.partsCtrl().updateDrillScale();
    if (obj().scriptTrigger().get(0)) {
        reqStar();
    }
    if (obj().scriptTrigger().get(3)) {
        custom.partsCtrl().growDrill();
    }
    if (obj().scriptTrigger().get(4)) {
        custom.partsCtrl().shrinkDrill();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePunch::procMove() {}

void StatePunch::procFixPos() {}

void StatePunch::reqStar() {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector2 pos = obj().location().pos().getXY();
    pos.y = custom.landCtrl().getFloorY();
    switch (obj().model().anim().currentG3DAnimIndex()) {
    case 0xC:
        pos.x = obj().model().model().nodes().at(0x18).worldTrans().x + param._B8 * obj().target().getSign();
        break;
    case 0xD:
        pos.x = obj().model().model().nodes().at(0xF).worldTrans().x;
        break;
    }
    Vector2 speed = param._14;
    Vector2 accel = param._1C;
    Utility::GenerateStarEffect(obj(), pos, speed, accel, static_cast<map::BinEnemyVariation>(0x19B));
    speed.x *= -1.0f;
    accel.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, accel, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::hrd3
