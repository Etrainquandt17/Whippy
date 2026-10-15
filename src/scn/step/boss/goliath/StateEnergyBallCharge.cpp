#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/goliath/StateEnergyBallCharge.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
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
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateEnergyBallThrow.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
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
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/Custom.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}}}}  // namespace scn::step::boss::goliath

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::goliathenergyball::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateEnergyBallCharge::StateEnergyBallCharge(Boss* boss, u32 _1, u32 _2, f32 _3)
    : StateBase(boss), mFrame(0), mTime(_1), mThrowTime(_2), mThrowSpeed(_3), mStartPos(boss->location().pos()), mWeapon(),
      mShakeWait(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x2C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(5));
}

StateEnergyBallCharge::~StateEnergyBallCharge() {}

void StateEnergyBallCharge::procAnim() {
    const Param& param = obj().param().goliath();
    if (mFrame < mTime) {
        mFrame++;
        if (mFrame == param._C4) {
            reqWeapon();
        }
        updateMotion();
    } else {
        obj().stateChanger().setNextState<StateEnergyBallThrow, Boss*, ObjRefHandle<weapon::Weapon>, u32, f32>(
            objPtr(), mWeapon, mThrowTime, mThrowSpeed);
    }
}

void StateEnergyBallCharge::procMove() {
    const Param& param = obj().param().goliath();
    if (mFrame > param._C4) {
        f32 t = static_cast<f32>(mFrame - param._C4) / static_cast<f32>(mTime - param._C4);
        f32 rate = Math::SinDegF(90.0f * t);
        Vector3 pos = mStartPos;
        pos.y += Math::Interpolate(0.0f, param._C8, rate);
        obj().location().setPos(pos);
    }
}

void StateEnergyBallCharge::procFixPos() {}

void StateEnergyBallCharge::reqWeapon() {
    const Param& param = obj().param().goliath();
    Vector2 pos = obj().location().pos().getXY();
    pos.y += param._D4;
    Vector2 speed = Vector2::ZERO;
    weapon::Desc desc(static_cast<weapon::Kind>(0x45), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        u32 frame = static_cast<f32>(mTime) * param._C0;
        weapon::goliathenergyball::Custom& weaponCustom =
            DynamicCastToRef<weapon::goliathenergyball::Custom, weapon::ICustom>(weapon->custom());
        weaponCustom.setScaleUpFrame(frame);
        mWeapon = weapon;
    }
}

void StateEnergyBallCharge::updateMotion() {
    const Param& param = obj().param().goliath();
    f32 rate = param._C0;
    f32 chargeTime = static_cast<f32>(mTime) * rate;
    switch (obj().model().getCurrentScriptIndex()) {
    case 0x2C:
        if (static_cast<f32>(mFrame) > 0.5f * chargeTime) {
            obj().model().reqScript(0x2D);
        }
        break;
    case 0x2D:
        if (static_cast<f32>(mFrame) > 0.9f * chargeTime) {
            obj().model().reqScript(0x2E);
        }
        break;
    case 0x2E:
        if (mShakeWait != 0) {
            mShakeWait--;
        } else {
            mShakeWait = 4;
            obj().model().shake().request(static_cast<chara::ShakeKind>(2));
        }
        break;
    }
}

}}}}  // namespace scn::step::boss::goliath
