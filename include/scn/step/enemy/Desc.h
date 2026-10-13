#ifndef SCN_STEP_ENEMY_DESC_H
#define SCN_STEP_ENEMY_DESC_H

#include "hel/math/Vector2.h"
#include "scn/step/map/BinEnemyDirType.h"
#include "scn/step/map/BinEnemyKind.h"
#include "scn/step/map/BinEnemySize.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Desc {
public:
    Desc(map::BinEnemyKind kind, map::BinEnemyVariation variation, u32 _8, map::BinEnemyDirType dirType, map::BinEnemySize size,
         bool _14, bool _15, const hel::math::Vector2& pos);

    map::BinEnemyKind mKind;
    map::BinEnemyVariation mVariation;
    u32 _8;
    map::BinEnemyDirType mDirType;
    map::BinEnemySize mSize;
    bool _14;
    bool _15;
    hel::math::Vector2 _18;
    hel::math::Vector2 _20;
    bool _28;
    bool _29;
    u32 _2C;
};

}}}  // namespace scn::step::enemy

#endif
