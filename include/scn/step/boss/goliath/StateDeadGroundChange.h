#ifndef SCN_STEP_BOSS_GOLIATH_STATEDEADGROUNDCHANGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEDEADGROUNDCHANGE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateDeadGroundChange : public StateBase {
public:
    StateDeadGroundChange(Boss* boss);
    virtual ~StateDeadGroundChange();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void changeGround();
    void reqItem();
    void reqGroundBreakEffect();
    u32 mFrame;
};

}}}}  // namespace scn::step::boss::goliath

#endif
