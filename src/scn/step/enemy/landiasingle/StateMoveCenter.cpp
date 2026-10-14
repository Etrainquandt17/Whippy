#include "scn/step/enemy/landiasingle/StateMoveCenter.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateWait.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateMoveCenter::StateMoveCenter(Enemy* enemy) : StateBase(enemy), mFrame(0), mStart(), mEnd() {
    obj().model().reqScript(8);
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    mEnd = obj().getBasePos();
    if (mEnd.x > mStart.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

StateMoveCenter::~StateMoveCenter() {}

void StateMoveCenter::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._40) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateMoveCenter::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._40);
    f32 rate = Math::SinDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateMoveCenter::procFixPos() {}

}}}}  // namespace scn::step::enemy::landiasingle
