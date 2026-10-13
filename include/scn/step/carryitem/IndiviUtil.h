#ifndef SCN_STEP_CARRYITEM_INDIVIUTIL_H
#define SCN_STEP_CARRYITEM_INDIVIUTIL_H

#include "scn/step/map/BinCarryItemKind.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class IndiviUtil {
public:
    static bool IsStageItem(map::BinCarryItemKind kind);
    static bool IsUniqueItem(map::BinCarryItemKind kind);
    static bool HasShadow(map::BinCarryItemKind kind);
    static bool IsRideItem(map::BinCarryItemKind kind);
    static bool IsReflectOnCollide(map::BinCarryItemKind kind);
    static bool IsDeadOnDamageField(CarryItem& carryItem);
    static bool IsDeadByStrongEnemy(CarryItem& carryItem);
};

}}}  // namespace scn::step::carryitem

#endif
