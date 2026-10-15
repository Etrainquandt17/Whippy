#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHEROSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHEROSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallJumpFarHeroStart : public StateBase {
public:
    StateWallJumpFarHeroStart(Boss* boss, f32 _1, u32 _2);
    virtual ~StateWallJumpFarHeroStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
    u32 _C;
};

}}}}  // namespace scn::step::boss::goliath

#endif
