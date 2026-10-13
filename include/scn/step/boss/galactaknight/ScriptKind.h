#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_SCRIPTKIND_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_SCRIPTKIND_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

// TODO: the other values; these are named after the bindings that pass them.
enum ScriptKind {
    ScriptKind_AirJumpFall = 3,
    ScriptKind_BackStep = 5,
    ScriptKind_Jump = 7,
    ScriptKind_JumpEnd = 8,
    ScriptKind_Walk = 9,
    ScriptKind_Attack1 = 14,
    ScriptKind_Attack2 = 15,
    ScriptKind_Attack3 = 16,
    ScriptKind_AttackFinish = 18,
    ScriptKind_AttackHi = 19,
    ScriptKind_AirSpin = 20,
    ScriptKind_AirSpinFall = 21,
    ScriptKind_AttackThrust = 23,
    ScriptKind_AttackThrustEnd = 24,
    ScriptKind_SwordBeamAttack = 33,
    ScriptKind_SwordBeamRain = 34,
    ScriptKind_TornadoAttackRise = 35,
};

}
}
}
}

#endif
