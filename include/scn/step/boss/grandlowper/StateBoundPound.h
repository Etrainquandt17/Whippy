#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEBOUNDPOUND_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEBOUNDPOUND_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateBoundPound : public IState {
public:
    struct Desc {
        u32 _0;
        f32 _4;
        f32 _8;
        f32 _C;
        f32 _10;
        f32 _14;
        f32 _18;
    };

    StateBoundPound(Boss* boss, const Desc& desc);
    virtual ~StateBoundPound();
};

}

}
}
}

#endif
