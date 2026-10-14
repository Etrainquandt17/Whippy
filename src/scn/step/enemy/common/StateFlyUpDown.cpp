#include "scn/step/enemy/common/StateFlyUpDown.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFlyUpDown::StateFlyUpDown(Enemy* enemy) : StateBase(enemy), mAngle(0.0f), mBaseY(enemy->location().pos().y) {
    obj().footState().setAir();
    obj().model().reqScript(4);
}

StateFlyUpDown::~StateFlyUpDown() {}

void StateFlyUpDown::procAnim() {}

void StateFlyUpDown::procMove() {
    mAngle += 1.5f;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    f32 offset = 1.75f * Math::SinDegF(mAngle);
    Vector3 pos = obj().location().pos();
    pos.y = mBaseY + offset;
    obj().location().setPos(pos);
}

void StateFlyUpDown::procFixPos() {
    if (obj().mapColl().result().mIsHitRoof) {
        mAngle = 90.0f;
        f32 offset = 1.75f * Math::SinDegF(mAngle);
        mBaseY = obj().location().pos().y - offset;
    }
    if (obj().mapColl().result().mIsHitFloor) {
        mAngle = 270.0f;
        f32 offset = 1.75f * Math::SinDegF(mAngle);
        mBaseY = obj().location().pos().y - offset;
    }
}

}}}}  // namespace scn::step::enemy::common
