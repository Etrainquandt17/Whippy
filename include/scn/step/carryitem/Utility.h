#ifndef SCN_STEP_CARRYITEM_UTILITY_H
#define SCN_STEP_CARRYITEM_UTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class Utility {
public:
    static bool IsSearchCollide(CarryItem& carryItem);
    static bool InScreen(CarryItem& carryItem, f32 margin);
    static void OnCrash(CarryItem& carryItem);
};

}}}  // namespace scn::step::carryitem

#endif
