#ifndef SCN_STEP_BOSS_BONKERS_STATEJUMPBIGSTART_H
#define SCN_STEP_BOSS_BONKERS_STATEJUMPBIGSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateJumpBigStart : public StateBase {
public:
    StateJumpBigStart(Boss* boss);
    virtual ~StateJumpBigStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::bonkers

#endif
