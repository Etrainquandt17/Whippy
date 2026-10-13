#ifndef SCN_STEP_BOSS_KINGSDOO_STATEJUMPMACHINEGUNSTART_H
#define SCN_STEP_BOSS_KINGSDOO_STATEJUMPMACHINEGUNSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

class StateJumpMachinegunStart : public StateBase {
public:
    StateJumpMachinegunStart(Boss* boss);
    virtual ~StateJumpMachinegunStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
