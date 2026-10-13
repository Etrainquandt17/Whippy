#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATESWORDBEAMATTACK_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATESWORDBEAMATTACK_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateSwordBeamAttack : public StateBase {
public:
    StateSwordBeamAttack(Boss* boss, ScriptKind kind);
    virtual ~StateSwordBeamAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsStart;
    u32 mWait;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
