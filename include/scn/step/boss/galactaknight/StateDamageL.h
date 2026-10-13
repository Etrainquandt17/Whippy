#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEDAMAGEL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEDAMAGEL_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateDamageL : public StateBase {
public:
    StateDamageL(Boss* boss);
    virtual ~StateDamageL();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
