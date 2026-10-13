#include "scn/step/item/StateCallback.h"

#include "scn/step/chara/LandConstraint.h"
#include "scn/step/item/Item.h"

namespace scn {
namespace step {
namespace item {

StateCallback::StateCallback(Item& item)
    : mObj(item) {}

void StateCallback::onStateChanged(const util::IStateChanger&) {
    mObj.landConstraint().resetMode();
}

}}}  // namespace scn::step::item
