#ifndef SCN_STEP_ENEMY_BARRACU_PARAMDATA_H
#define SCN_STEP_ENEMY_BARRACU_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

// TODO: the name is a guess: nothing in the game names what Param::barracu() returns.
struct ParamData {
    struct Level {
        f32 mSpeed;
        f32 _4;
        f32 _8;
    };

    Level mLevel[3];
    f32 mTurnSpeed;
    u32 mAttackDamageFrame;
    u32 mAttackDamage;
    u32 mAttackEndFrame;
    u32 mAttackResistFrame;
    u32 _38;
    f32 mEscapeSpeed;
    u32 mEscapeFrame;
    f32 mSearchRadius;
    f32 mSearchOffset;
    u32 mEffectFrame;
    f32 mMapCheckX;
    f32 mMapCheckY;
};

}}}}  // namespace scn::step::enemy::barracu

#endif
