#ifndef SCN_STEP_BOSS_WATERGALBOROS_STATEATTACK_H
#define SCN_STEP_BOSS_WATERGALBOROS_STATEATTACK_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class StateAttack : public StateBase {
public:
    StateAttack(Boss* boss, u32 scriptKind);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mScriptKind;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
