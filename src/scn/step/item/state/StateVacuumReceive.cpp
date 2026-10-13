#include "scn/step/item/state/StateVacuumReceive.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "scn/step/chara/Lifetime.h"
#include "scn/step/chara/Model.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"
#include "scn/step/item/RotAnim.h"
#include "scn/step/item/VacuumReceiver.h"

namespace scn {
namespace step {
namespace item {
namespace state {

StateVacuumReceive::StateVacuumReceive(Item* item, u32 time)
    : StateBase(item)
    , mMoveAlgorithm() {
    obj().rotAnim().setIsEnable(false);
    hel::math::Vector2 offs = obj().location().pos().getXY() - obj().vacuumReceiver().getAttackerPos();
    hel::math::Vector2 centerOffs = obj().centerOffs();
    f32 scale = 1.0f;
    mMoveAlgorithm.init(offs, centerOffs, scale, time);
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().lifetime().setAgeless();
    obj().move().resetVelocity();
    obj().setCanCatch(false);
    obj().setCanGather(false);
}

StateVacuumReceive::~StateVacuumReceive() {
    obj().rotAnim().setIsEnable(true);
}

void StateVacuumReceive::procAnim() {
    if (mMoveAlgorithm.isEnd()) {
        obj().vacuumReceiver().setEndVacuumed();
        obj().onCatched();
        obj().dead();
    }
    mMoveAlgorithm.update();
}

void StateVacuumReceive::procFixPos() {
    hel::math::Vector2 pos = obj().vacuumReceiver().getAttackerPos() + mMoveAlgorithm.getNextOffs();
    obj().location().setPos(pos.toVector3());
    obj().model().setCustomMtx(mMoveAlgorithm.getRotMtx());
}

}}}}  // namespace scn::step::item::state
