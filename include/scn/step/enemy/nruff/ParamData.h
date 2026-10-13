#ifndef SCN_STEP_ENEMY_NRUFF_PARAMDATA_H
#define SCN_STEP_ENEMY_NRUFF_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

// TODO: the name is a guess: nothing in the game names what Param::nruff() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[31];
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::nruff

#endif
