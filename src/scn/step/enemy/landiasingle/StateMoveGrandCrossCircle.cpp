#include "scn/step/enemy/landiasingle/StateMoveGrandCrossCircle.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
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

StateMoveGrandCrossCircle::StateMoveGrandCrossCircle(Enemy* enemy) : StateBase(enemy), mFrame(0), mStart(), mEnd() {
    const ParamData& param = obj().param().landiasingle();
    obj().model().reqScript(8);
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    mEnd = obj().comp().mainCamera().getCenter();
    mEnd.y += param._3c;
    switch (obj().level()) {
    case 0:
        mEnd.y += param._38;
        break;
    case 1:
        mEnd.x -= param._34;
        break;
    case 2:
        mEnd.y -= param._38;
        break;
    case 3:
        mEnd.x += param._34;
        break;
    }
    if (mEnd.x > mStart.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

StateMoveGrandCrossCircle::~StateMoveGrandCrossCircle() {}

void StateMoveGrandCrossCircle::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._124) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateMoveGrandCrossCircle::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._124);
    f32 rate = Math::SinDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateMoveGrandCrossCircle::procFixPos() {}

}}}}  // namespace scn::step::enemy::landiasingle
