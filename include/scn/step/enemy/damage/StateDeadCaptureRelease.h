#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDEADCAPTURERELEASE_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDEADCAPTURERELEASE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDeadCaptureRelease : public StateBase {
public:
    StateDeadCaptureRelease(Enemy* enemy, bool isRight);
    virtual ~StateDeadCaptureRelease();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::damage

#endif
