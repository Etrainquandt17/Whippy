#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEFLYZ_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEFLYZ_H

#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateFlyZ : public StateBase {
public:
    StateFlyZ(Boss* boss, f32 margin);
    virtual ~StateFlyZ();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mSign;
    hel::math::Direction3 mDir;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
