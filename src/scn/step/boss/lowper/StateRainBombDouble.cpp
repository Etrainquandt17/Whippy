#include "scn/step/boss/lowper/StateRainBombDouble.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateRainBombDouble::StateRainBombDouble(Boss* boss, const Vector3& pos, u32 frame, u32 interval, u32 count)
    : StateBase(boss), mStartPos(), mGoalPos(), mCount(0), mFrame(frame), mInterval(0), mIntervalFrame(interval), mShotCount(count),
      mIsShotEnd(false), mIsStarted(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos = custom.waftMoveCtrl().getCenter();
    mGoalPos = obj().basePos().toVector3() + pos;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.4f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x12);
}

StateRainBombDouble::~StateRainBombDouble() {}

void StateRainBombDouble::procAnim() {
    if (mIsStarted && mCount < mFrame) {
        mCount++;
    }
    if (obj().scriptTrigger().get(0)) {
        reqBullet(1.75f);
        reqBullet(-1.25f);
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0x14);
        mIsShotEnd = true;
        mIsStarted = true;
    }
    if (mShotCount != 0 && mInterval == 0) {
        if (mIsShotEnd == true) {
            obj().model().reqScript(0x13);
            mInterval = mIntervalFrame;
            mIsShotEnd = false;
            mShotCount--;
        }
    } else {
        mInterval--;
    }
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateRainBombDouble::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 intervalRate = static_cast<f32>(mInterval) / static_cast<f32>(mIntervalFrame);
    f32 wave = Math::AbsF32(Math::SinDegF(90.0f * intervalRate));
    f32 offsetY = 1.5f * (wave - 1.0f);
    pos.y += offsetY;
    custom.waftMoveCtrl().setCenter(pos);
}

void StateRainBombDouble::procFixPos() {}

void StateRainBombDouble::reqBullet(f32 offsetX) {
    Vector3 pos = obj().location().pos();
    pos.x += offsetX * obj().target().getSign();
    Vector3 speed(0.0f, 0.01f, 0.0f);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(1), pos, speed, 0);
}

}}}}  // namespace scn::step::boss::lowper
