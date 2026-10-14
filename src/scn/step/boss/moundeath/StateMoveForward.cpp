#include "scn/step/boss/moundeath/StateMoveForward.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/chara/Model.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateMoveForward::StateMoveForward(Boss* boss) : StateBase(boss), mCount(0) {
    obj().footState().setGround();
    obj().model().reqScript(6);
    obj().brainCtrl().toValid();
}

StateMoveForward::~StateMoveForward() {}

void StateMoveForward::procAnim() {
    const Param& param = obj().param().moundeath();
    if (++mCount % param._60 == 0) {
        Utility::TurnHatedHero(obj());
    }
}

void StateMoveForward::procMove() {
    const Param& param = obj().param().moundeath();
    f32 total = obj().model().anim().totalFrame();
    f32 t = obj().model().anim().frame() / total;
    int deg = static_cast<int>(70.0f + 720.0f * t) % 360;
    f32 rate = 0.5f * (1.0f + Math::SinDegF(deg));
    rate *= rate;
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(param._54 * rate, param._58 * rate, param._5C));
}

void StateMoveForward::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::moundeath
