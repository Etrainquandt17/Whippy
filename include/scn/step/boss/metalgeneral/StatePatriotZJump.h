#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTZJUMP_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTZJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/StatePatriotGenerate.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StatePatriotZJump : public StateBase {
public:
    StatePatriotZJump(Boss* boss, StatePatriotGenerate::Config config);
    virtual ~StatePatriotZJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    StatePatriotGenerate::Config mConfig;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
