#include "scn/step/boss/galactaknight/StateAttack.h"

#include "app/Random.h"
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
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
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
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateAttack::StateAttack(Boss* boss, const AttackDesc& desc)
    : StateBase(boss), mFrame(desc._8), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mIsMove(false),
      mIsMoonShot(desc._D) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = desc._4 * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    if (desc._C) {
        Utility::ControlHateOnAction(obj());
    }
    if (desc._E) {
        obj().guard().setType(static_cast<GuardType>(1));
    }
    obj().model().reqScript(desc._0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateAttack::~StateAttack() {
    obj().soundSE().loop().stop();
}

void StateAttack::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        obj().brainCtrl().toValid();
    }
    if (obj().scriptTrigger().get(1) && mFrame != 0) {
        mIsMove = true;
    }
    if (obj().scriptTrigger().get(2)) {
        generateStar();
    }
    if (mIsMoonShot && obj().scriptTrigger().get(3)) {
        generateMoonShot();
    }
    if (mCount < mFrame) {
        if (mIsMove) {
            mCount++;
        }
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateAttack::procMove() {
    if (mIsMove) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        f32 rate = hel::math::Math::SinDegF(90.0f * t);
        hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
        obj().location().setPos(pos);
    }
}

void StateAttack::procFixPos() {}

void StateAttack::generateStar() {
    const Param& param = obj().param().galactaknight();
    hel::math::Vector2 pos = param._C;
    hel::math::Vector2 speed = param._1C;
    pos.x *= obj().target().getSign();
    speed.x *= obj().target().getSign();
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

void StateAttack::generateMoonShot() {
    const Param& param = obj().param().galactaknight();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos.y += param._A8;
    hel::math::Vector2 start = pos;
    start.x += param._A0 * obj().target().getSign();
    hel::math::Vector2 dir = hel::math::Vector2::BASIS_X;
    dir.x *= obj().target().getSign();
    dir *= param._9C;
    u32 variation = 0;
    f32 heroY = Utility::GetHatedHeroPos(obj()).y;
    if (heroY > param._A4 + custom.landCtrl().getFloorY()) {
        variation = 1;
    }
    weapon::Desc desc(static_cast<weapon::Kind>(0x88), variation, static_cast<ostop::Flag>(8), start, pos, dir,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::galactaknight
