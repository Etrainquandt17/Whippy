#ifndef SCN_STEP_BOSS_LANDIA_STATETAILSTART_H
#define SCN_STEP_BOSS_LANDIA_STATETAILSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateTailStart : public StateBase {
public:
    StateTailStart(Boss* boss);
    virtual ~StateTailStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
};

}}}}  // namespace scn::step::boss::landia

#endif
