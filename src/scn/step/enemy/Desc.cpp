#include "scn/step/enemy/Desc.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {

Desc::Desc(map::BinEnemyKind kind, map::BinEnemyVariation variation, u32 _8, map::BinEnemyDirType dirType, map::BinEnemySize size,
           bool _14, bool _15, const Vector2& pos)
    : mKind(kind)
    , mVariation(variation)
    , _8(_8)
    , mDirType(dirType)
    , mSize(size)
    , _14(_14)
    , _15(_15)
    , _18(pos)
    , _20(pos)
    , _28(false)
    , _29(false)
    , _2C(0) {}

}}}  // namespace scn::step::enemy
