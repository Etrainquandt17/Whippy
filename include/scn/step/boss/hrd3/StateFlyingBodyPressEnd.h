#ifndef SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSEND_H
#define SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSEND_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateFlyingBodyPressEnd : public StateBase {
public:
    StateFlyingBodyPressEnd(Boss* boss);
    virtual ~StateFlyingBodyPressEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqStar();

    u32 mCount;
    hel::math::Vector3 mStartPos;
    f32 mGoalY;
    bool mIsMove;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
