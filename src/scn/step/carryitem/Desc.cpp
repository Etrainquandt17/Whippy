#include "scn/step/carryitem/Desc.h"

namespace scn {
namespace step {
namespace carryitem {

Desc::Desc(map::BinCarryItemKind kind, u32 _4, bool _8, const hel::math::Vector2& _C, u32 useCount)
    : kind(kind)
    , _4(_4)
    , _8(_8)
    , _C(_C)
    , useCount(useCount) {}

}}}  // namespace scn::step::carryitem
