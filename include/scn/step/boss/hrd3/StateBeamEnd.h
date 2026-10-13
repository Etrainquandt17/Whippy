#ifndef SCN_STEP_BOSS_HRD3_STATEBEAMEND_H
#define SCN_STEP_BOSS_HRD3_STATEBEAMEND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateBeamEnd : public StateBase {
public:
    StateBeamEnd(Boss* boss);
    virtual ~StateBeamEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::hrd3

#endif
