#include "scn/step/carryitem/lockkey/Utility.h"

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

bool Utility::IsDanger(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().lockKey()._0;
}

}}}}  // namespace scn::step::carryitem::lockkey
