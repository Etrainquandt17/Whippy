#ifndef SCN_STEP_CARRYITEM_LOCKKEY_UTILITY_H
#define SCN_STEP_CARRYITEM_LOCKKEY_UTILITY_H

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

class Utility {
public:
    static bool IsDanger(CarryItem& carryItem);
};

}}}}  // namespace scn::step::carryitem::lockkey

#endif
