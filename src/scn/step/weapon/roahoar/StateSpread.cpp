#include "scn/step/weapon/roahoar/StateSpread.h"

#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahoar/Param.h"
#include "scn/step/weapon/roahoar/StateMoveStart.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

StateSpread::StateSpread(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().roahOar();
    obj().culling().setValid(false);
    obj().target().setIsRightDir(false);
    obj().model().reqScript(0);
    mStartPos = obj().location().pos();
    mEndPos.x = mStartPos.x;
    mEndPos.y = mStartPos.y;
    switch (obj().variation()) {
    case 0:
        mEndPos.z = -1.0f * param._C;
        break;
    case 1:
        mEndPos.z = 3.0f * param._C;
        break;
    case 2:
        mEndPos.z = -2.0f * param._C;
        break;
    case 3:
        mEndPos.z = param._C;
        break;
    case 4:
        mEndPos.z = -3.0f * param._C;
        break;
    case 5:
        mEndPos.z = 2.0f * param._C;
        break;
    }
}

StateSpread::~StateSpread() {}

void StateSpread::procAnim() {
    const Param& param = obj().param().roahOar();
    if (mFrame < param._10) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateMoveStart, Weapon*>(&obj());
        return;
    }
    if (Utility::IsExtra(obj())) {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param._10);
        f32 sin = hel::math::Math::SinDegF(90.0f * rate);
        f32 scale = sin * param._8 + 1.0f;
        obj().model().setBaseScale(hel::math::Vector3::ALL_ONE * scale);
        if (mFrame % 5 == 0) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
        }
    }
}

void StateSpread::procMove() {
    const Param& param = obj().param().roahOar();
    f32 t = hel::math::Math::InterpolationParamMinToMin(static_cast<f32>(mFrame) / static_cast<f32>(param._10));
    obj().location().setPos(hel::math::Math::LinearInterpolation(mStartPos, mEndPos, t));
}

void StateSpread::procFixPos() {}

}}}}  // namespace scn::step::weapon::roahoar
