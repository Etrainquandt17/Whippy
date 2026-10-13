#ifndef SCN_STEP_ITEM_DESC_H
#define SCN_STEP_ITEM_DESC_H

#include "hel/math/Vec2.h"
#include "hel/math/Vector2.h"
#include "scn/step/map/BinItemKind.h"
#include "scn/step/map/BinItemVariation.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

// TODO: name the members.
class Desc {
public:
    Desc(map::BinItemKind kind, u32 _4, bool _8, map::BinItemVariation variation, const hel::math::Vector2& pos);

    map::BinItemKind mKind;
    u32 _4;
    bool _8;
    map::BinItemVariation mVariation;
    // TODO: the two vectors are assigned as hel::math::Vector2 in the constructor without being constructed first,
    // which a Vector2 member would be; what they are is not known.
    hel::math::Vec2 mPos;
    bool _18;
    hel::math::Vec2 _1C;
};

}}}  // namespace scn::step::item

#endif
