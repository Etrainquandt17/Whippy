#ifndef SCN_STEP_ENEMY_COMMON_STATEFLUSH_H
#define SCN_STEP_ENEMY_COMMON_STATEFLUSH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateFlush : public StateBase {
public:
    StateFlush(Enemy* enemy);
    virtual void procMove();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::enemy::common

#endif
