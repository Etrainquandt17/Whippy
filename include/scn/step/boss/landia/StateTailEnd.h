#ifndef SCN_STEP_BOSS_LANDIA_STATETAILEND_H
#define SCN_STEP_BOSS_LANDIA_STATETAILEND_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateTailEnd : public StateBase {
public:
    StateTailEnd(Boss* boss);
    virtual ~StateTailEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::landia

#endif
