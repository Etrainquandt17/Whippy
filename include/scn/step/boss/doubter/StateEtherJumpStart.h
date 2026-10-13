#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPSTART_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpStart : public StateBase {
public:
    StateEtherJumpStart(Boss* boss, u32 count);
    virtual ~StateEtherJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::doubter

#endif
