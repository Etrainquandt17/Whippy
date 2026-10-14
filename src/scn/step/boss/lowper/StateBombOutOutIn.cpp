#include "scn/step/boss/lowper/StateBombOutOutIn.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateBombOutOutIn::StateBombOutOutIn(Boss* boss)
    : StateBase(boss), mCount(0), mInY(0.0f), mOutY(0.0f), mStartX(0.0f), mGoalX(0.0f), mIntpRate(0.0f), mXRate(0.0f), mPhase(0),
      mRotH(0.0f) {
    mRotH = obj().model().rotCtrl().getRotH();
    obj().model().reqScript(0xE);
    Rect rect = obj().comp().mainCamera().getWorldRect();
    f32 baseX = obj().basePos().x;
    f32 sign = obj().location().pos().x >= baseX ? 1.0f : -1.0f;
    mInY = rect._0 - 1.5f;
    mOutY = rect._0 - 4.0f;
    mStartX = obj().basePos().x + 6.0f * sign;
    mGoalX = obj().basePos().x - 6.0f * sign;
}

StateBombOutOutIn::~StateBombOutOutIn() {}

void StateBombOutOutIn::procAnim() {
    mCount++;
    if (obj().scriptTrigger().get(0)) {
        reqBomb();
        mXRate = 0.0f;
        mPhase++;
    }
    if (mCount == 260) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    mRotH += 8.0f;
    if (mRotH >= 360.0f) {
        mRotH -= 360.0f;
    }
    obj().model().rotCtrl().initRotH(mRotH);
}

// TODO: the original keeps the time rate in f30 and the phase rate in f31; here they are the other way round.
void StateBombOutOutIn::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mIntpRate += 0.05f;
    if (mIntpRate > 1.0f) {
        mIntpRate = 1.0f;
    }
    mXRate += 0.0015f;
    if (mXRate > 1.0f) {
        mXRate = 1.0f;
    }
    f32 t = static_cast<f32>(mCount) / 260.0f;
    Vector2 pos;
    f32 rate = 0.0f;
    switch (mPhase) {
    case 0:
        rate = 0.0f;
        break;
    case 1:
        rate = 1.0f;
        break;
    case 2:
        rate = 0.5f;
        break;
    }
    f32 x = obj().location().pos().x;
    f32 targetX = mStartX * (1.0f - rate) + mGoalX * rate;
    pos.x = x * (1.0f - mXRate) + targetX * mXRate;
    f32 rateY = Math::AbsF32(Math::SinDegF(720.0f * t));
    pos.y = mOutY * (1.0f - rateY) + mInY * rateY;
    custom.waftMoveCtrl().setMoveIntpRate(mIntpRate);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos.toVector3());
}

void StateBombOutOutIn::procFixPos() {}

void StateBombOutOutIn::reqBomb() {
    Vector3 pos = obj().location().pos();
    Vector3 speed(0.0f, -1.0f, 0.0f);
    speed *= 0.1f;
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(1), pos, speed, 0);
}

}}}}  // namespace scn::step::boss::lowper
