#ifndef SCN_STEP_ENEMY_SIRKIBBLE_PARAMDATA_H
#define SCN_STEP_ENEMY_SIRKIBBLE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

// TODO: the name is a guess: nothing in the game names what Param::sirkibble() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mAttackShotFrame;
    f32 mWeaponOffsetX;
    f32 mWeaponSpeed;
    u32 mJumpStartFrame;
    f32 mJumpSpeed;
    gobj::MoveParamFall mJumpFall;
    u32 mJumpAttackShotFrame;
};

}}}}  // namespace scn::step::enemy::sirkibble

#endif
