#ifndef SCN_STEP_CARRYITEM_INDIVIUTIL_H
#define SCN_STEP_CARRYITEM_INDIVIUTIL_H

#include "scn/step/map/BinCarryItemKind.h"

namespace scn {
namespace step {
namespace carryitem {

class IndiviUtil {
public:
    static bool IsStageItem(map::BinCarryItemKind kind);
    static bool IsUniqueItem(map::BinCarryItemKind kind);
};

}}}  // namespace scn::step::carryitem

#endif
