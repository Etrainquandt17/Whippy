#include "scn/step/boss/metalgeneral/StateCircling.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlight.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateCircling::StateCircling(Boss* boss) : StateBase(boss), mCount(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x1B);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
}

StateCircling::~StateCircling() {
    obj().model().rotCtrl().initRotV(0.0f);
}

void StateCircling::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (mCount < param._174) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateCirclingFlight, Boss*>(objPtr());
        return;
    }
    f32 rot = 360.0f * (static_cast<f32>(mCount) / static_cast<f32>(param._174));
    if (!obj().target().isRightDir()) {
        rot *= -1.0f;
    }
    obj().model().rotCtrl().initRotV(rot);
}

void StateCircling::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._174);
    Vector3 pos = mStartPos;
    f32 x = Math::SinDegF(360.0f * t);
    if (static_cast<f32>(mCount + 1) < static_cast<f32>(param._174) / 2.0f) {
        x *= 0.3f;
    }
    pos.x += x * param._178 * obj().target().getSign();
    f32 y = Math::SinDegF(180.0f * t);
    pos.y += y * param._17C;
    obj().location().setPos(pos);
}

void StateCircling::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
