#ifndef SCN_STEP_BOSS_COMMON_STATEFALL_H
#define SCN_STEP_BOSS_COMMON_STATEFALL_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateFall : public StateBase {
public:
    static bool TryToChangeState(Boss* boss);

    StateFall(Boss* boss);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::common

#endif
