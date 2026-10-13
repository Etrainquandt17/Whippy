#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEWARPOUT_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEWARPOUT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateWarpOut : public IState {
public:
    StateWarpOut(Boss* boss, const hel::math::Vector3& pos, bool _2, bool spMove = false);
    virtual ~StateWarpOut();
};

}

}}}  // namespace scn::step::boss

#endif
