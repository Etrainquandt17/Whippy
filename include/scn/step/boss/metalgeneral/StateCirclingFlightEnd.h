#ifndef SCN_STEP_BOSS_METALGENERAL_STATECIRCLINGFLIGHTEND_H
#define SCN_STEP_BOSS_METALGENERAL_STATECIRCLINGFLIGHTEND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StateCirclingFlightEnd : public StateBase {
public:
    StateCirclingFlightEnd(Boss* boss);
    virtual ~StateCirclingFlightEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
