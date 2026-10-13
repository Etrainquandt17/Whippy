#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGWALLHIT_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGWALLHIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellRollingWallHit : public StateBase {
public:
    StateSwellRollingWallHit(Boss* boss);
    virtual ~StateSwellRollingWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
