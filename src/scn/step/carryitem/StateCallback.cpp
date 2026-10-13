#include "scn/step/carryitem/StateCallback.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/ObjCollLite.h"

namespace scn {
namespace step {
namespace carryitem {

StateCallback::StateCallback(CarryItem& carryItem)
    : mObj(carryItem) {}

void StateCallback::onStateChanged(const util::IStateChanger&) {
    mObj.landConstraint().resetMode();
    mObj.objColl().clearAttack();
    mObj.flash().unset();
}

}}}  // namespace scn::step::carryitem
