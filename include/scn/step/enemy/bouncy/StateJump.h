#ifndef SCN_STEP_ENEMY_BOUNCY_STATEJUMP_H
#define SCN_STEP_ENEMY_BOUNCY_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bouncy {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedH;
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::bouncy

#endif
