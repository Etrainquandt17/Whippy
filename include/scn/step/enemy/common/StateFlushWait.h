#ifndef SCN_STEP_ENEMY_COMMON_STATEFLUSHWAIT_H
#define SCN_STEP_ENEMY_COMMON_STATEFLUSHWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateFlushWait : public StateBase {
public:
    StateFlushWait(Enemy* enemy);
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::common

#endif
