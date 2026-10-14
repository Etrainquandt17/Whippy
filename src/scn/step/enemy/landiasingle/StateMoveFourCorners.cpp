#include "scn/step/enemy/landiasingle/StateMoveFourCorners.h"

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

StateMoveFourCorners::StateMoveFourCorners(Enemy* enemy, Config config)
    : StateBase(enemy), mFrame(0), mStart(), mEnd(), mConfig(config) {
    const ParamData& param = obj().param().landiasingle();
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    mEnd = obj().comp().mainCamera().getCenter();
    mEnd.y += param._3c;
    f32 sign = mConfig._0 ? 1.0f : -1.0f;
    switch (obj().level()) {
    case 0:
        mEnd.x -= param._34 * sign;
        {
            f32 y = mEnd.y + param._38;
            mEnd.y = y + mConfig._4;
        }
        break;
    case 1:
        mEnd.x -= param._34 * sign;
        mEnd.y -= param._38;
        break;
    case 2:
        mEnd.x += param._34 * sign;
        mEnd.y -= param._38;
        break;
    case 3:
        mEnd.x += param._34 * sign;
        {
            f32 y = mEnd.y + param._38;
            mEnd.y = y + mConfig._4;
        }
        break;
    }
    if (Math::EqZero(mEnd.x - mStart.x)) {
        obj().model().reqScript(0);
    } else {
        obj().model().reqScript(8);
        if (mEnd.x > mStart.x) {
            obj().target().setIsRightDir(true);
        } else {
            obj().target().setIsRightDir(false);
        }
    }
}

StateMoveFourCorners::~StateMoveFourCorners() {}

void StateMoveFourCorners::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._b4) {
        mFrame++;
        if (mFrame == param._b8) {
            f32 centerX = obj().comp().mainCamera().getCenter().x;
            if (mEnd.x < centerX) {
                obj().target().setIsRightDir(true);
            } else {
                obj().target().setIsRightDir(false);
            }
        }
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), false);
    }
}

void StateMoveFourCorners::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._b4);
    f32 rate = Math::SinDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateMoveFourCorners::procFixPos() {}

}}}}  // namespace scn::step::enemy::landiasingle
