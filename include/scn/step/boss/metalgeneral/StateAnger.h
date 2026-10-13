#ifndef SCN_STEP_BOSS_METALGENERAL_STATEANGER_H
#define SCN_STEP_BOSS_METALGENERAL_STATEANGER_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateAnger : public StateBase {
public:
    StateAnger(Boss* boss);
    virtual ~StateAnger();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
