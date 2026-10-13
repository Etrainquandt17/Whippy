#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS

#include "scn/step/boss/dubior/StateMoveToOtherSide.h"

#include "app/Random.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

namespace {

const u32 WaitFrameTable[] = { 10, 30, 10, 10 };

}

StateMoveToOtherSide::StateMoveToOtherSide(Boss* boss) : StateBase(boss), mTargets(), mCount(0), mIndex(0) {
    const Param& param = obj().param().dubior();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    f32 sign = obj().location().pos().x > obj().comp().mainCamera().getCenter().x ? -1.0f : 1.0f;
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector3 target(obj().comp().mainCamera().getCenter().x + sign * param.mHeightAdjustDistance,
                              param.mFirstOffsY + obj().basePos().y, 0.0f);
    obj().target().setIsRightDir(sign > 0.0f);
    f32 wave = -1.0f;
    for (u32 i = 0; i < 4; i++) {
        u32 index = i;
        if (i == 0) {
            index = 1;
        } else if (i == 1) {
            index = 0;
        }
        f32 rate = (index + 1) / 4.0f;
        hel::math::Vector3 point = pos * (1.0f - rate) + target * rate;
        if (index + 1 < 4) {
            point.y += wave * (param.mMoveWaveRange * app::Random::RandNF() + param.mMoveWaveOffset);
        }
        mTargets.add(point);
        wave *= -1.0f;
    }
    custom.setBodyCollFastMove();
    obj().soundSE().normal().start(0x59D);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x4F5), obj().location().pos());
}

StateMoveToOtherSide::~StateMoveToOtherSide() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
    mTargets.clear();
}

void StateMoveToOtherSide::procAnim() {
    mCount++;
    if (mCount >= WaitFrameTable[mIndex]) {
        mCount = 0;
        mIndex++;
        if (mIndex >= 4) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        } else {
            obj().soundSE().normal().start(0x59D);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0x4F5), obj().location().pos());
        }
    }
}

void StateMoveToOtherSide::procMove() {
    hel::math::Vector3 target = mTargets[mIndex];
    hel::math::Vector3 pos = obj().location().pos() * 0.5f + target * 0.5f;
    obj().location().setPos(pos);
}

void StateMoveToOtherSide::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
