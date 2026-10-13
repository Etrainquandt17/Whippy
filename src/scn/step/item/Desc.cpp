#include "scn/step/item/Desc.h"

namespace scn {
namespace step {
namespace item {

Desc::Desc(map::BinItemKind kind, u32 _4, bool _8, map::BinItemVariation variation, const hel::math::Vector2& pos)
    : mKind(kind)
    , _4(_4)
    , _8(_8)
    , mVariation(variation) {
    *reinterpret_cast<hel::math::Vector2*>(&mPos) = pos;
    _18 = false;
    *reinterpret_cast<hel::math::Vector2*>(&_1C) = pos;
}

}}}  // namespace scn::step::item
