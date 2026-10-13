#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEBOUNDPOUNDFINISH_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEBOUNDPOUNDFINISH_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateBoundPoundFinish : public IState {
public:
    struct Desc {
        u32 _0;
        u32 _4;
        f32 _8;
        f32 _C;
        f32 _10;
        f32 _14;
        f32 _18;
        f32 _1C;
    };

    StateBoundPoundFinish(Boss* boss, const Desc& desc);
    virtual ~StateBoundPoundFinish();
};

}

}}}  // namespace scn::step::boss

#endif
