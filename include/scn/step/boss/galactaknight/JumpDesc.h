#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_JUMPDESC_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_JUMPDESC_H

#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class JumpDesc {
public:
    JumpDesc(ScriptKind kind, f32, f32, u32);

    ScriptKind _0;
    f32 _4;
    f32 _8;
    u32 _C;
    bool _10;
    bool _11;
    bool _12;
    bool _13;
    bool _14;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
