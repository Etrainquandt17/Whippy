#include "scn/step/boss/hrd3/StateFlyingBodyPressRise.h"

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
#include "scn/step/boss/hrd3/StateFlyingBodyPressFall.h"
#include "scn/step/boss/hrd3/StateWait.h"
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
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateFlyingBodyPressRise::StateFlyingBodyPressRise(Boss* boss)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mIsMove(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1B);
    setTargetPos();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    Utility::ControlHateOnAction(obj());
    obj().guard().setType(static_cast<GuardType>(2));
}

StateFlyingBodyPressRise::~StateFlyingBodyPressRise() {}

void StateFlyingBodyPressRise::procAnim() {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
        custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    }
    if (mIsMove) {
        if (mCount < param._D4) {
            mCount++;
            if (mCount == param._D8) {
                obj().soundSE().normal().start(0x3D2);
            }
        } else {
            obj().stateChanger().setNextState<StateFlyingBodyPressFall, Boss*>(objPtr());
            return;
        }
    }
    if (mCount <= param._D8) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._D8);
        f32 rot = 1.0f - hel::math::Math::CosDegF(90.0f * t);
        rot *= -custom.partsCtrl().getMaxRotV() * obj().target().getSign();
        obj().model().rotCtrl().initRotV(rot);
    } else {
        f32 t = static_cast<f32>(mCount - param._D8) / static_cast<f32>(param._D4 - param._D8);
        t = hel::math::Math::LimitMinMax(t, 0.0f, 1.0f);
        f32 rate = 1.0f - (3.0f * (t * t) - 2.0f * t * (t * t));
        f32 rot = 360.0f * rate + -custom.partsCtrl().getMaxRotV();
        rot *= obj().target().getSign();
        obj().model().rotCtrl().initRotV(rot);
    }
}

void StateFlyingBodyPressRise::procMove() {
    if (mIsMove) {
        const Param& param = obj().param().hrd3();
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._D4);
        f32 fall = 1.0f - hel::math::Math::SinDegF(90.0f * t);
        f32 rateY = 1.0f - fall * (fall * (fall * (fall * fall)));
        f32 rateX = hel::math::Math::SinDegF(90.0f * t);
        hel::math::Vector3 pos;
        pos.x = hel::math::Math::LinearInterpolation(mStartPos.x, mGoalPos.x, rateX);
        pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rateY);
        pos.z = mGoalPos.z;
        obj().location().setPos(pos);
    }
}

void StateFlyingBodyPressRise::procFixPos() {}

void StateFlyingBodyPressRise::setTargetPos() {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.y = obj().param().hrd3()._E0 + custom.landCtrl().getFloorY();
    mGoalPos.x = Utility::GetHatedHeroPos(obj()).x;
    mGoalPos.x = custom.landCtrl().getAdjustX(
        mGoalPos.x, param._C + param._E8, param._C + param._DC, obj().target().isRightDir()
    );
    mGoalPos.z = mStartPos.z;
}

}}}}  // namespace scn::step::boss::hrd3
