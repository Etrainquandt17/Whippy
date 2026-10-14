#include "scn/step/boss/lowper/StateSparkAttackRolling.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/DamageFlash.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/Manager.h"
#include "scn/step/sfx/ReverseWorld.h"
#include "scn/step/sfx/ScreenFade.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/ICustom.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/lowperrollingspark/Custom.h"
#include "util/ObjRefHandle.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}}}}  // namespace scn::step::boss::lowper

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::lowperrollingspark::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSparkAttackRolling::StateSparkAttackRolling(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(), mGoalPos(), mRot(0.0f), mWeapons() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = Math::AbsF32(rect._C - rect._8);
    f32 sign = Math::Sign(obj().location().pos().x - obj().basePos().x);
    mStartPos = obj().location().pos();
    mGoalPos.x = obj().basePos().x - sign * (0.5f * width - 0.5f);
    mGoalPos.y = mStartPos.y;
    obj().model().reqScript(0x1E);
    obj().guard().setType(static_cast<GuardType>(1));
    obj().hitStop().setArmor();
    obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x1BF));
    reqWeapon();
    setAttack();
}

StateSparkAttackRolling::~StateSparkAttackRolling() {
    obj().objColl().clearAttack(1);
    obj().soundSE().loop().stop();
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateSparkAttackRolling::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 t2 = t * t;
    f32 rate = 3.0f * t2 - 2.0f * t * t2;
    f32 rotX = 360.0f * rate;
    mRot += 20.0f;
    {
        NodeAccessor node = obj().model().model().nodes().at(3);
        node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(rotX, 0.0f, 0.0f)) *
                                 Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot, 0.0f)));
    }
    Vector2 pos = obj().location().pos().getXY();
    pos.y += 0.65f;
    for (int i = 0; i < 8; i++) {
        if (mWeapons[i].isAlive()) {
            DynamicCastToRef<weapon::lowperrollingspark::Custom, weapon::ICustom>(mWeapons[i].ref().custom())
                .setCenterPos(pos);
        }
    }
}

void StateSparkAttackRolling::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateSparkAttackRolling::procFixPos() {}

void StateSparkAttackRolling::setAttack() {
    obj().objColl().clearAttack(1);
    obj().objColl().addAttack(1, 0, 0.7f, Vector2(0.0f, 0.65f));
    obj().effect().state().requestN(static_cast<effect::Kind>(0x39E), 3);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().soundSE().loop().start(0x1B2);
    obj().soundSE().normal().start(0x574);
}

void StateSparkAttackRolling::reqWeapon() {
    f32 sign = Math::Sign(obj().location().pos().x - obj().basePos().x);
    Vector3 pos = obj().location().pos();
    pos.y += 0.65f;
    weapon::Desc desc(static_cast<weapon::Kind>(0x82), 0, static_cast<ostop::Flag>(8), pos.getXY(), Vector2::ZERO,
                      obj().objColl().owner());
    for (int i = 0; i < 4; i++) {
        f32 y = 1.25f * (i + 1);
        Vector2 offset(0.0f, y);
        desc._24 = offset;
        mWeapons[i * 2] = obj().comp().weaponManager().request(desc);
        desc._24 = -offset;
        mWeapons[i * 2 + 1] = obj().comp().weaponManager().request(desc);
    }
    for (int i = 0; i < 8; i++) {
        if (mWeapons[i].isAlive()) {
            weapon::lowperrollingspark::Custom& custom =
                DynamicCastToRef<weapon::lowperrollingspark::Custom, weapon::ICustom>(mWeapons[i].ref().custom());
            custom.setTotalFrame(mFrame);
            custom.setDelayFrame(i / 2 * 5);
            custom.setRotAngle(360.0f * sign);
            custom.setCenterPos(pos.getXY());
        }
    }
}

}}}}  // namespace scn::step::boss::lowper
