#ifndef SCN_STEP_BOSS_COMMON_STATEMOVEDESC_H
#define SCN_STEP_BOSS_COMMON_STATEMOVEDESC_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateMoveDesc {
public:
    StateMoveDesc(gobj::MoveParamAccel accel);

    gobj::MoveParamAccel _0;
};

}}}}  // namespace scn::step::boss::common

#endif
