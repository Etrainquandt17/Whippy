#include "scn/step/boss/Desc.h"

namespace scn {
namespace step {
namespace boss {

Desc::Desc()
    : mIsValid(false), mKind(map::BinBossKind_0), mVariation(map::BinBossVariation_0), mLevel(0), mIsSuper(false), mPos(), mCamOffs(),
      _24(0) {}

Desc::Desc(map::BinBossKind kind, map::BinBossVariation variation, u32 level, bool isSuper, const hel::math::Vector2& pos,
           const hel::math::Vector2& camOffs)
    : mIsValid(true), mKind(kind), mVariation(variation), mLevel(level), mIsSuper(isSuper), mPos(pos), mCamOffs(camOffs), _24(0) {}

}
}
}
