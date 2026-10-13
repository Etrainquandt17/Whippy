#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTFALL_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTFALL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StatePatriotFall : public StateBase {
public:
    StatePatriotFall(Boss* boss);
    virtual ~StatePatriotFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
