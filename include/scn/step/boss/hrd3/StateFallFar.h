#ifndef SCN_STEP_BOSS_HRD3_STATEFALLFAR_H
#define SCN_STEP_BOSS_HRD3_STATEFALLFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateFallFar : public StateBase {
public:
    StateFallFar(Boss* boss, u32 frame, const hel::math::Vector3& pos);
    virtual ~StateFallFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    f32 mGoalY;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
