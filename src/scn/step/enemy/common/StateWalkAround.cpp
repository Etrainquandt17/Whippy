#include "scn/step/enemy/common/StateWalkAround.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateWalkAround::StateWalkAround(Enemy* enemy) : StateBase(enemy), mBaseX(enemy->location().pos().x) {
    switch (enemy->level()) {
    case 0:
        mAccel = gobj::MoveParamAccel::Create(0.02f, 0.001f, 0.001f);
        break;
    case 1:
        mAccel = gobj::MoveParamAccel::Create(0.03f, 0.002f, 0.001f);
        break;
    case 2:
        mAccel = gobj::MoveParamAccel::Create(0.04f, 0.003f, 0.001f);
        break;
    default:
        mAccel = gobj::MoveParamAccel::Create(0.06f, 0.004f, 0.001f);
        break;
    }
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().model().setFrameRate(mAccel._0 / 0.02f);
    obj().brainCtrl().toValid();
}

StateWalkAround::~StateWalkAround() {}

void StateWalkAround::procAnim() {}

void StateWalkAround::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
}

void StateWalkAround::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
        f32 x = obj().location().pos().x;
        mBaseX = x + 2.5f * obj().target().getSign();
    } else {
        f32 diff = obj().location().pos().x - mBaseX;
        if (hel::math::Math::Abs(diff) > 2.0f) {
            obj().target().setIsRightDir(diff < 0.0f);
        }
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
