#include "scn/step/item/state/StateFixed.h"

#include "scn/step/item/Item.h"
#include "scn/step/item/RotAnim.h"
#include "scn/step/ogen/Generator.h"

namespace scn {
namespace step {
namespace item {
namespace state {

StateFixed::StateFixed(Item* item)
    : StateBase(item) {
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
}

void StateFixed::procMove() {
    if (obj().objGenerator() != 0) {
        obj().location().setPos(obj().objGenerator()->pos().toVector3());
    }
}

}}}}  // namespace scn::step::item::state
