#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallJumpStart : public StateBase {
public:
    StateWallJumpStart(Boss* boss, f32 _1, u32 _2);
    virtual ~StateWallJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
    u32 _C;
};

}}}}  // namespace scn::step::boss::goliath

#endif
