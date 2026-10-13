#ifndef SCN_STEP_ENEMY_FATTYBUFFERJR_PARAMDATA_H
#define SCN_STEP_ENEMY_FATTYBUFFERJR_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

// TODO: the names are guesses: nothing in the game names what Param::fattybufferjr() returns.
struct ParamData {
    struct Air {
        gobj::MoveParamDecel mDecel;
        gobj::MoveParamFall mFall;
    };

    Air mAppear;
    Air mJump;
    f32 mEscapeEndZ;
    hel::math::Vec3 mEscapeVelocity;
    Air mEscape;
};

}}}}  // namespace scn::step::enemy::fattybufferjr

#endif
