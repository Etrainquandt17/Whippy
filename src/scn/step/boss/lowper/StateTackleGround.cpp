#include "scn/step/boss/lowper/StateTackleGround.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateTackleGround::StateTackleGround(Boss* boss, u32 frame, f32 distance)
    : StateBase(boss), mCount(0), mFrame(frame), mY(0.0f), mStartX(0.0f), mGoalX(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE);
    f32 baseX = obj().basePos().x;
    f32 sign = Math::SignF32(obj().location().pos().x - baseX);
    mY = param._38 + obj().basePos().y;
    mStartX = obj().location().pos().x;
    mGoalX = obj().basePos().x - sign * distance;
    obj().model().reqScript(0xA);
}

StateTackleGround::~StateTackleGround() {}

void StateTackleGround::procAnim() {
    mCount++;
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleGround::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos;
    f32 cos = Math::CosDegF(180.0f * t);
    f32 rate = 0.5f * (1.0f + cos);
    pos.x = Math::Interpolate(mGoalX, mStartX, rate);
    pos.y = mY;
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateTackleGround::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
