#ifndef SCN_STEP_CARRYITEM_STEPSHOE_UTILITY_H
#define SCN_STEP_CARRYITEM_STEPSHOE_UTILITY_H

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

class Utility {
public:
    static bool IsWarn(CarryItem& carryItem);
    static bool IsDanger(CarryItem& carryItem);
    static bool ChkLifeTime(CarryItem& carryItem);
    static void SetFlash(CarryItem& carryItem);
    static void ReqFlashEffect(CarryItem& carryItem);
    static f32 UpdateBodyFlash(CarryItem& carryItem, f32 angle);
};

}}}}  // namespace scn::step::carryitem::stepshoe

#endif
