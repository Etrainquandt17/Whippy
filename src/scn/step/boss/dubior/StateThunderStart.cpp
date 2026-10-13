#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS

#include "scn/step/boss/dubior/StateThunderStart.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateThunder.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

namespace {

const u32 WaitFrameTable[] = { 10, 10 };

}

StateThunderStart::StateThunderStart(Boss* boss) : StateBase(boss), mTargets(), mCount(0), mIndex(0), _2C(0) {
    const Param& param = obj().param().dubior();
    obj().footState().setAir();
    obj().model().reqScript(9);
    Utility::ControlHateOnAction(obj());
    Utility::TurnHatedHero(obj());
    hel::math::Vector3 pos = obj().location().pos();
    f32 targetY = param.mFirstOffsY + obj().basePos().y;
    hel::math::Vector3 target(Utility::GetHatedHeroPos(obj()).x, targetY, 0.0f);
    f32 sign = -1.0f;
    for (u32 i = 0; i < 2; i++) {
        f32 rate = (i + 1) / 2.0f;
        hel::math::Vector3 point = pos * (1.0f - rate) + target * rate;
        if (i + 1 < 2) {
            point.y += sign * (param.mThunderRandRange * app::Random::RandNF()) + param.mThunderOffsetY;
        }
        mTargets.add(point);
        sign *= -1.0f;
    }
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollFastMove();
    obj().soundSE().normal().start(0x59D);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x4F5), obj().location().pos());
}

StateThunderStart::~StateThunderStart() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateThunderStart::procAnim() {
    mCount++;
    if (mCount >= WaitFrameTable[mIndex]) {
        mCount = 0;
        mIndex++;
        if (mIndex >= 2) {
            obj().stateChanger().setNextState<StateThunder, Boss*>(objPtr());
        } else {
            obj().soundSE().normal().start(0x59D);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0x4F5), obj().location().pos());
        }
    }
}

void StateThunderStart::procMove() {
    hel::math::Vector3 target = mTargets[mIndex];
    hel::math::Vector3 pos = obj().location().pos() * 0.5f + target * 0.5f;
    obj().location().setPos(pos);
}

void StateThunderStart::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
