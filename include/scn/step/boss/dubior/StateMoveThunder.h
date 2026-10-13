#ifndef SCN_STEP_BOSS_DUBIOR_STATEMOVETHUNDER_H
#define SCN_STEP_BOSS_DUBIOR_STATEMOVETHUNDER_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateMoveThunder : public StateBase {
public:
    StateMoveThunder(Boss* boss);
    virtual ~StateMoveThunder();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mTime;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mTargetPos;
    int mPhase;
};

}}}}  // namespace scn::step::boss::dubior

#endif
