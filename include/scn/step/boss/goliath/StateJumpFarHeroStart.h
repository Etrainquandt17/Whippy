#ifndef SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHEROSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHEROSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateJumpFarHeroStart : public StateBase {
public:
    StateJumpFarHeroStart(Boss* boss, u32 _1, f32 _2);
    virtual ~StateJumpFarHeroStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    f32 _C;
};

}}}}  // namespace scn::step::boss::goliath

#endif
