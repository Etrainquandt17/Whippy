#include "scn/step/carryitem/common/StateVacuumReceive.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Lifetime.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

StateVacuumReceive::StateVacuumReceive(CarryItem* carryItem, u32 time)
    : StateBase(carryItem)
    , mMoveAlgorithm()
    , mWasAgeless(obj().lifetime().isAgeless())
    , mIsRight(false) {
    hel::math::Vector2 dir(0.0f, 0.5f);
    hel::math::Vector2 pos = obj().location().pos().getXY();
    hel::math::Vector2 attackerPos = obj().vacuumReceiver().getAttackerPos();
    mMoveAlgorithm.init(pos - attackerPos, dir, 1.0f, time);
    mIsRight = pos.x >= attackerPos.x;
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().setCanGather(false);
    obj().setCanOpenDoor(false);
    if (!mWasAgeless) {
        obj().lifetime().setAgeless();
    }
    obj().move().resetVelocity();
}

StateVacuumReceive::~StateVacuumReceive() {
    if (!mWasAgeless) {
        obj().lifetime().unsetAgeless();
    }
    obj().setCanOpenDoor(true);
    obj().setCanGather(true);
    obj().vacuumReceiver().setIsValid(true);
    obj().mapColl().setValid(true);
    obj().clearCheckRadiusPrevOwner();
}

void StateVacuumReceive::procAnim() {
    if (mMoveAlgorithm.isEnd()) {
        if (obj().kind() == 0) {
            obj().vacuumReceiver().setEndVacuumed();
            obj().dead();
        } else {
            hel::math::Vector3 pos = obj().location().pos();
            obj().location().setPos(obj().vacuumReceiver().getAttackerPos().toVector3());
            obj().mapColl().setValid(true);
            obj().location().setPos(pos);
            obj().mapColl().procMapColl();
            obj().vacuumReceiver().setEndVacuumed();
            obj().move().setSpeedH(mIsRight ? -0.04f : 0.04f);
            obj().move().setSpeedV(0.1f);
            obj().setNextStateDefault();
        }
    }
    mMoveAlgorithm.update();
}

void StateVacuumReceive::procFixPos() {
    hel::math::Vector2 pos = obj().vacuumReceiver().getAttackerPos() + mMoveAlgorithm.getNextOffs();
    obj().location().setPos(pos.toVector3());
}

}}}}  // namespace scn::step::carryitem::common
