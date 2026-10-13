#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTMOVETOFAR_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTMOVETOFAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StatePatriotMoveToFar : public StateBase {
public:
    StatePatriotMoveToFar(Boss* boss);
    virtual ~StatePatriotMoveToFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
