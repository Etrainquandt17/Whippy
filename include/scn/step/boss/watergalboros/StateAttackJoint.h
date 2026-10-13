#ifndef SCN_STEP_BOSS_WATERGALBOROS_STATEATTACKJOINT_H
#define SCN_STEP_BOSS_WATERGALBOROS_STATEATTACKJOINT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class StateAttackJoint : public StateBase {
public:
    StateAttackJoint(Boss* boss, u32 scriptKind);
    virtual ~StateAttackJoint();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
