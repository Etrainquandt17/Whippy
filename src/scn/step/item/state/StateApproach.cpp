#include "scn/step/item/state/StateApproach.h"

#include "scn/step/Component.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateApproach::StateApproach(Item* item)
    : StateBase(item)
    , mRate(0.0f) {
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
}

void StateApproach::procAnim() {}

void StateApproach::procMove() {
    const Param& param = obj().param();
    Vector3 mainPos = obj().comp().heroManager().getMainPlayerPos();
    Vector3 pos = obj().location().pos() * (1.0f - mRate) + mainPos * mRate;
    obj().location().setPos(pos);
    mRate += param._64;
    if (mRate > 1.0f) {
        mRate = 1.0f;
    }
}

}}}}  // namespace scn::step::item::state
