#ifndef SCN_STEP_BOSS_DESC_H
#define SCN_STEP_BOSS_DESC_H

#include "hel/math/Vector2.h"
#include "scn/step/map/BinBossKind.h"
#include "scn/step/map/BinBossVariation.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

// TODO: name the members.
class Desc {
public:
    Desc();
    Desc(map::BinBossKind kind, map::BinBossVariation variation, u32 level, bool isSuper, const hel::math::Vector2& pos,
         const hel::math::Vector2& camOffs);

    bool mIsValid;
    map::BinBossKind mKind;
    map::BinBossVariation mVariation;
    u32 mLevel;
    bool mIsSuper;
    hel::math::Vector2 mPos;
    hel::math::Vector2 mCamOffs;
    u32 _24;
};

}}}  // namespace scn::step::boss

#endif
