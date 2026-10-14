#include "scn/step/carryitem/common/StateSpaceJump.h"

#include "gobj/Move.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

StateSpaceJump::StateSpaceJump(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem) {
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().move().resetVelocity();
    obj().setCanGather(false);
    obj().model().setVisibility(false);
    obj().effect().releaseAndVanish();
    obj().effectBack().releaseAndVanish();
    obj().effectWarp().releaseAndVanish();
}

StateSpaceJump::~StateSpaceJump() {
    obj().setCanGather(true);
    obj().vacuumReceiver().setIsValid(true);
    obj().mapColl().setValid(true);
    obj().model().setVisibility(true);
    obj().onSpaceJumpEnd();
}

void StateSpaceJump::procAnim() {
    mUseAlgorithm.procAnim();
}

void StateSpaceJump::procMove() {
    mUseAlgorithm.procMove();
}

void StateSpaceJump::procConstraint() {
    mUseAlgorithm.procConstraint();
}

}}}}  // namespace scn::step::carryitem::common
