#include "scn/step/boss/lowper/StateWarpIn.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateWarpIn::StateWarpIn(Boss* boss) : StateBase(boss), mCount(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().reqScript(0x18);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.enemyCtrl().sendSignalBarrierWarpIn();
}

StateWarpIn::~StateWarpIn() {
    obj().model().setVisibility(true);
    obj().model().resetScale();
}

void StateWarpIn::procAnim() {
    if (mCount < 20) {
        mCount++;
        if (mCount == 20) {
            obj().model().setVisibility(false);
            obj().brainCtrl().toValid();
        }
    }
    f32 t = static_cast<f32>(mCount) / 20.0f;
    f32 width = 0.01f + (1.0f - t);
    Vector3 scale(width, t * t + 1.0f, width);
    obj().model().setScale(scale);
}

void StateWarpIn::procMove() {}

void StateWarpIn::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
