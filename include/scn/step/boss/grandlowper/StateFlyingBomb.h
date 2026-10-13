#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEFLYINGBOMB_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEFLYINGBOMB_H

#include "scn/step/boss/IState.h"
#include "scn/step/boss/grandlowper/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateFlyingBomb : public IState {
public:
    StateFlyingBomb(Boss* boss, f32 _1, ScriptKind kind, bool divide);
    virtual ~StateFlyingBomb();
};

}

}}}  // namespace scn::step::boss

#endif
