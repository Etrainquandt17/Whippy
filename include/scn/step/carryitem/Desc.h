#ifndef SCN_STEP_CARRYITEM_DESC_H
#define SCN_STEP_CARRYITEM_DESC_H

#include "hel/math/Vector2.h"
#include "scn/step/map/BinCarryItemKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class Desc {
public:
    map::BinCarryItemKind kind;
    u32 _4;
    bool _8;
    hel::math::Vector2 _C;
    u32 useCount;
};

}}}  // namespace scn::step::carryitem

#endif
