#include "scn/step/carryitem/invisiblestone/StateUse.h"

#include "gobj/Location.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/invisiblestone/StateFall.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/core/PermEffect.h"

namespace scn {
namespace step {
namespace carryitem {
namespace invisiblestone {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem)
    , mFrame(0) {
    mUseAlgorithm.setOffset(hel::math::Vector3(0.0f, -0.2f, 0.0f));
    obj().effect().release();
    if (obj().useCount() < obj().param().invisibleStone()._0) {
        obj().effect().requestN(static_cast<effect::Kind>(0x349), 1);
    } else {
        obj().effect().requestN(static_cast<effect::Kind>(0x34A), 1);
    }
}

StateUse::~StateUse() {}

void StateUse::procAnim() {
    mUseAlgorithm.procAnim();
    mFrame++;
    obj().incUseCount();
    if (obj().useCount() >= obj().param().invisibleStone()._4) {
        if (mFrame >= obj().param().invisibleStone()._8) {
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x34C),
                                                        obj().location().pos() + hel::math::Vector3(0.0f, 0.5f, 0.0f));
            obj().soundSE().start(0x100);
            obj().dead();
        }
    } else if (obj().useCount() == obj().param().invisibleStone()._0) {
        obj().effect().release();
        obj().effect().requestN(static_cast<effect::Kind>(0x34A), 1);
    }
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    if (mUseAlgorithm.procConstraint()) {
        obj().stateChanger().setNextState<StateFall, CarryItem*>(objPtr());
    }
}

}}}}  // namespace scn::step::carryitem::invisiblestone
