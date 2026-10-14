#include "scn/step/boss/lowper/StateGlideShot.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateGlideShot::StateGlideShot(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mShotCount(0), mStartY(0.0f), mGoalY(0.0f), mGoalX(0.0f), mStartX(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE);
    Utility::ControlHateOnAction(obj());
    f32 baseX = obj().basePos().x;
    f32 sign = Math::SignF32(obj().location().pos().x - baseX);
    mStartY = obj().comp().mainCamera().getWorldRect()._0 - param._5C;
    mGoalY = param._58 + obj().basePos().y;
    mGoalX = obj().basePos().x + 0.5f * sign * param._54;
    mStartX = obj().basePos().x - 0.5f * sign * param._54;
    obj().model().reqScript(0xA);
}

StateGlideShot::~StateGlideShot() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().resetBarrierRadius();
}

void StateGlideShot::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mCount++;
    f32 radius = custom.enemyCtrl().getBarrierRadius();
    custom.enemyCtrl().setBarrierRadius(0.9f * radius);
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    } else if (mShotCount != 0) {
        mShotCount--;
    } else {
        mShotCount = 20;
        custom.enemyCtrl().request(enemy::lowperbullet::VariationKind_Homing, obj().location().pos(), Vector3::ZERO, 0);
    }
}

void StateGlideShot::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector2 pos;
    f32 cos = Math::CosDegF(180.0f * t);
    f32 rateX = 0.5f * (1.0f + cos);
    pos.x = Math::LinearInterpolation(mStartX, mGoalX, rateX);
    f32 sin = Math::SinDegF(180.0f * t);
    f32 rateY = 1.0f - sin;
    pos.y = Math::LinearInterpolation(mGoalY, mStartY, rateY);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.waftMoveCtrl().setMoveIntpRate(param._60);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos.toVector3());
}

void StateGlideShot::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
