#include "scn/step/enemy/doubtersnake/StateWalk.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/doubtersnake/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy), mAngle(0.0f) {
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().brainCtrl().toValid();
}

StateWalk::~StateWalk() {}

void StateWalk::procAnim() {}

void StateWalk::procMove() {
    const ParamData& param = obj().param().doubtersnake();
    mAngle += param.mWalkAngleSpeed;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    gobj::MoveParamAccel accel = param.mWalkAccel;
    accel._0 += param.mWalkAccelAdd * (0.5f * (1.0f - hel::math::Math::CosDegF(mAngle)));
    obj().move().groundAccel(obj().target().isRightDir(), accel);
}

void StateWalk::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWallFront()) {
        obj().move().resetSpeedH();
        obj().target().invert();
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::doubtersnake
