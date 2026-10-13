#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPRESTART_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPRESTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpRestart : public StateBase {
public:
    StateEtherJumpRestart(Boss* boss, u32 count);
    virtual ~StateEtherJumpRestart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::doubter

#endif
