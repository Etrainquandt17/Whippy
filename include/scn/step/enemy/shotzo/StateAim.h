#ifndef SCN_STEP_ENEMY_SHOTZO_STATEAIM_H
#define SCN_STEP_ENEMY_SHOTZO_STATEAIM_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace shotzo {

class StateAim : public StateBase {
public:
    StateAim(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 roundAngle(f32 angle);
    
    u32 mFrame;
    f32 mStartAngle;
    f32 mEndAngle;
};

}}}}  // namespace scn::step::enemy::shotzo

#endif
