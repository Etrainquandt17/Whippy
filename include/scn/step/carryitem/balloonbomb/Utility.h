#ifndef SCN_STEP_CARRYITEM_BALLOONBOMB_UTILITY_H
#define SCN_STEP_CARRYITEM_BALLOONBOMB_UTILITY_H

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace balloonbomb {

class Utility {
public:
    static bool IsDrop(CarryItem& carryItem);
    static bool IsDanger(CarryItem& carryItem);
    static bool IsExplode(CarryItem& carryItem);
    static void UpdateFlash(CarryItem& carryItem, f32 wave);
    static bool ChangeStateInWater(CarryItem* carryItem);
};

}}}}  // namespace scn::step::carryitem::balloonbomb

#endif
