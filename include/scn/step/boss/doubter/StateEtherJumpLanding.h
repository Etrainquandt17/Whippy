#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPLANDING_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPLANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpLanding : public StateBase {
public:
    StateEtherJumpLanding(Boss* boss);
    virtual ~StateEtherJumpLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::doubter

#endif
