#include "scn/step/boss/galactaknight/StateAnger.h"

#include "app/Random.h"
#include "g3d/ColorAnimFlashOp.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/ColorF.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/CustomFlash.h"
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
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateAnger::StateAnger(Boss* boss)
    : StateBase(boss), mFrame(0), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mPhase(0), mFlashCount(0),
      mFlashFrame(80) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame = param._130;
    mGoalPos.x = param._134 * -obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    obj().model().reqScript(0x2A);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
    obj().invincible().setPermNoFlash();
}

StateAnger::~StateAnger() {
    obj().flash().custom().setIsValid(false);
    obj().infoBossPanel().transformEnd();
    obj().bgmCtrl().startBossBattleGalactaKnightPhase2();
}

void StateAnger::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        obj().infoBossPanel().transformStart();
        mPhase = 1;
        mFlashCount = 0;
        mFlashFrame = 80;
    }
    if (obj().scriptTrigger().get(1)) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x1A1), 2);
        mPhase = 2;
        mFlashCount = 0;
        mFlashFrame = obj().model().anim().totalFrame() - static_cast<u32>(obj().model().anim().frame());
    }
    if (mCount < mFrame) {
        mCount++;
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    updateColorFlash();
}

void StateAnger::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StateAnger::procFixPos() {}

void StateAnger::updateColorFlash() {
    const Param& param = obj().param().galactaknight();
    hel::common::ColorF color(0.0f, 0.0f, 0.0f, 1.0f);
    switch (mPhase) {
    case 0:
        obj().flash().custom().setIsValid(false);
        return;
    case 1: {
        mFlashCount++;
        f32 rate = static_cast<f32>(mFlashCount) / static_cast<f32>(mFlashFrame);
        f32 power = hel::math::Math::Abs(0.5f * hel::math::Math::SinDegF(90.0f * rate));
        color.set(power * (0.75f * (1.0f + hel::math::Math::SinDegF(720.0f * rate))),
                  power * (0.25f * (1.0f + hel::math::Math::SinDegF(720.0f * rate + 120.0f))),
                  power * (0.25f * (1.0f + hel::math::Math::SinDegF(720.0f * rate + 240.0f))), 1.0f);
        obj().flash().custom().setOperation(static_cast<g3d::ColorAnimFlashOp>(1));
        break;
    }
    case 2: {
        mFlashCount++;
        f32 rate = static_cast<f32>(mFlashCount) / static_cast<f32>(mFlashFrame);
        color.set(1.0f, 1.0f, 1.0f, hel::math::Math::CosDegF(90.0f * rate));
        obj().flash().custom().setOperation(static_cast<g3d::ColorAnimFlashOp>(0));
        break;
    }
    }
    obj().flash().custom().setIsValid(true);
    obj().flash().custom().setColor(color.toGXColorAsNormal());
}

}}}}  // namespace scn::step::boss::galactaknight
