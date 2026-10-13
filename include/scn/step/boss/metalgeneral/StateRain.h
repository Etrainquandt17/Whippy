#ifndef SCN_STEP_BOSS_METALGENERAL_STATERAIN_H
#define SCN_STEP_BOSS_METALGENERAL_STATERAIN_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StateRain : public StateBase {
public:
    StateRain(Boss* boss);
    virtual ~StateRain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
