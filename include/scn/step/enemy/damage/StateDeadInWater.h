#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDEADINWATER_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDEADINWATER_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDeadInWater : public StateBase {
public:
    StateDeadInWater(Enemy* enemy);
    virtual ~StateDeadInWater();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void deadFlash();

private:
    u32 mFrame;
    bool mIsSink;
    f32 mFrameRate;
    f32 mFlashAngle;
    f32 mFlashSpeed;
    f32 mFlashRate;
};

}}}}  // namespace scn::step::enemy::damage

#endif
