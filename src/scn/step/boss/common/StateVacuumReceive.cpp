#include "scn/step/boss/common/StateVacuumReceive.h"

#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/VacuumReceiver.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateVacuumReceive::StateVacuumReceive(Boss* boss) : StateBase(boss), mMove() {
    Vector2 offset = obj().location().pos().getXY() - obj().vacuumReceiver().getAttackerPos();
    Vector2 dir(0.0f, 1.0f);
    mMove.init(offset, dir, 0.4f, 30);
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().move().resetVelocity();
}

StateVacuumReceive::~StateVacuumReceive() {}

void StateVacuumReceive::procAnim() {
    if (mMove.isEnd()) {
        obj().vacuumReceiver().setEndVacuumed();
        obj().hitPoint().set(0);
        obj().dead();
    } else {
        mMove.update();
    }
}

void StateVacuumReceive::procMove() {}

void StateVacuumReceive::procFixPos() {
    obj().model().setScale(Vector3::ALL_ONE * mMove.getScale());
    Vector2 pos = obj().vacuumReceiver().getAttackerPos() + mMove.getNextOffs();
    obj().location().setPos(pos.toVector3());
}

}}}}  // namespace scn::step::boss::common
