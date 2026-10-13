#ifndef SCN_STEP_BOSS_HRD3_STATESWINGARMFAR_H
#define SCN_STEP_BOSS_HRD3_STATESWINGARMFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateSwingArmFar : public StateBase {
public:
    StateSwingArmFar(Boss* boss, u32 frame);
    virtual ~StateSwingArmFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsMove;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
