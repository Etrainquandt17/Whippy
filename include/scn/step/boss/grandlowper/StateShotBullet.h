#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATESHOTBULLET_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATESHOTBULLET_H

#include "scn/step/boss/IState.h"
#include "scn/step/boss/grandlowper/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateShotBullet : public IState {
public:
    StateShotBullet(Boss* boss, ScriptKind kind, f32 _2);
    virtual ~StateShotBullet();
};

}

}}}  // namespace scn::step::boss

#endif
