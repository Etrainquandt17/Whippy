#include "scn/step/boss/fattybuffer/StateMoveForward.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateMoveForward::StateMoveForward(Boss* boss, f32 rate) : StateBase(boss), mRate(rate) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateMoveForward::~StateMoveForward() {}

void StateMoveForward::procAnim() {
    const Param& param = obj().param().fattybuffer();
    if (obj().scriptTrigger().get(0)) {
        obj().brainCtrl().toValid();
    }
    if (obj().scriptTrigger().get(1)) {
        f32 speed = 0.5f * (param.mMoveForwardSpeed * (1.0f + mRate));
        obj().move().setSpeedH(speed * obj().target().getSign());
        obj().model().setFrameRate(mRate);
    }
}

void StateMoveForward::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._78);
}

void StateMoveForward::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
