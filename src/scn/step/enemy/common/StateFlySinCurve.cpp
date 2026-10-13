#include "scn/step/enemy/common/StateFlySinCurve.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

namespace {

// Its locals sit below procMove's own on the stack, so this was a function of its own.
inline void t_AirDecel(StateBase& state) {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    state.obj().move().airDecelFall(decel, fall);
}

}

StateFlySinCurve::StateFlySinCurve(Enemy* enemy)
    : StateBase(enemy), mAngle(0.0f), mBaseY(enemy->location().pos().y),
      mSpeedX(0.04f * (obj().target().isRightDir() ? 1.0f : -1.0f)) {
    obj().footState().setAir();
    obj().model().reqScript(4);
}

StateFlySinCurve::~StateFlySinCurve() {}

void StateFlySinCurve::procAnim() {}

void StateFlySinCurve::procMove() {
    t_AirDecel(*this);
    mAngle += 2.5f;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    f32 offset = 1.5f * hel::math::Math::SinDegF(mAngle);
    hel::math::Vector3 pos = obj().location().pos();
    pos.y = mBaseY + offset;
    pos.x += mSpeedX;
    obj().location().setPos(pos);
}

void StateFlySinCurve::procFixPos() {
    hel::math::Vector2 dir = obj().nururi().getNururiDir();
    if ((dir.x > 0.0f && !obj().target().isRightDir()) || (dir.x < 0.0f && obj().target().isRightDir())) {
        obj().target().invert();
        mSpeedX = -mSpeedX;
        hel::math::Vector3 pos = obj().location().pos();
        pos.x += 2.0f * mSpeedX;
        obj().location().setPos(pos);
    }
    if (obj().mapColl().result().isHitWall()) {
        mSpeedX = -mSpeedX;
        obj().target().setIsRightDir(mSpeedX >= 0.0f);
    }
    if (obj().mapColl().result().mIsHitRoof) {
        mAngle = 90.0f;
        mBaseY = obj().location().pos().y - 1.5f;
    } else if (obj().mapColl().result().mIsHitFloor) {
        mAngle = 270.0f;
        mBaseY = 1.5f + obj().location().pos().y;
    }
}

}
}
}
}
