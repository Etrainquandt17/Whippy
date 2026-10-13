#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATESPINATTACK_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATESPINATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateSpinAttack : public StateBase {
public:
    StateSpinAttack(Boss* boss, f32 distance, u32 frame);
    virtual ~StateSpinAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void generateStar();
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
