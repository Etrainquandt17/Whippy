#include "scn/step/boss/metalgeneral/StateNeedle.h"

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
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/boss/metalgeneral/StateLanding.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/boss/metalgeneral/States.h"
#include "scn/step/boss/metalgeneral/WeaponCtrl.h"
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
namespace metalgeneral {

StateNeedle::StateNeedle(Boss* boss, u32 index) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    switch (static_cast<int>(index)) {
    case 1:
        obj().model().reqScript(0x13);
        break;
    case 2:
        obj().model().reqScript(0x14);
        break;
    case 3:
        obj().model().reqScript(0x15);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
    obj().move().resetVelocity();
}

StateNeedle::~StateNeedle() {}

void StateNeedle::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        custom.weaponCtrl().reqNeedlePlus();
    }
    if (obj().scriptTrigger().get(1)) {
        custom.weaponCtrl().reqNeedleSlant();
    }
    if (obj().scriptTrigger().get(2)) {
        custom.weaponCtrl().reqNeedleAll();
    }
}

void StateNeedle::procMove() {}

void StateNeedle::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
