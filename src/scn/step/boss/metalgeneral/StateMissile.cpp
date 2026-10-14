#include "scn/step/boss/metalgeneral/StateMissile.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
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
#include "scn/step/boss/metalgeneral/StateAnger.h"
#include "scn/step/boss/metalgeneral/StateAppear.h"
#include "scn/step/boss/metalgeneral/StateCircling.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlight.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlightEnd.h"
#include "scn/step/boss/metalgeneral/StateDamageL.h"
#include "scn/step/boss/metalgeneral/StateDead.h"
#include "scn/step/boss/metalgeneral/StateDeadJump.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/boss/metalgeneral/StateFirst.h"
#include "scn/step/boss/metalgeneral/StateLanding.h"
#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"
#include "scn/step/boss/metalgeneral/StatePatriotFall.h"
#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"
#include "scn/step/boss/metalgeneral/StatePatriotMoveToFar.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackle.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleLower.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleUpper.h"
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
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateMissile::StateMissile(Boss* boss, u32 index) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    switch (index) {
    case 1:
        obj().model().reqScript(0x17);
        break;
    case 3:
        obj().model().reqScript(0x18);
        break;
    case 5:
        obj().model().reqScript(0x19);
        break;
    case 8:
        obj().model().reqScript(0x1A);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    obj().move().resetVelocity();
}

StateMissile::~StateMissile() {}

void StateMissile::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    Vector2 pos = obj().location().pos().getXY();
    pos += Vector2(param._150 * obj().target().getSign(), param._154);
    if (obj().scriptTrigger().get(1)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_0);
    }
    if (obj().scriptTrigger().get(2)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_1);
    }
    if (obj().scriptTrigger().get(3)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_2);
    }
}

void StateMissile::procMove() {}

void StateMissile::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
