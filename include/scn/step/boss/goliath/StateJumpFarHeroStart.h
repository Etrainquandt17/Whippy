#ifndef SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHEROSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHEROSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateJumpFarHeroStart : public IState {
public:
    StateJumpFarHeroStart(Boss* boss, u32 _1, f32 _2);
    virtual ~StateJumpFarHeroStart();
};

}}}}  // namespace scn::step::boss::goliath

#endif
