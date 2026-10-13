#ifndef SCN_STEP_BOSS_HRD3_STATEAPPEAR_H
#define SCN_STEP_BOSS_HRD3_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

// TODO: members.
class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss, bool isSkip);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::hrd3

#endif
