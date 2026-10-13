#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_ATTACKDESC_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_ATTACKDESC_H

#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class AttackDesc {
public:
    AttackDesc(ScriptKind kind, f32, u32, bool);
    AttackDesc(ScriptKind kind, bool);

    ScriptKind _0;
    f32 _4;
    u32 _8;
    bool _C;
    bool _D;
    bool _E;
};

}
}
}
}

#endif
