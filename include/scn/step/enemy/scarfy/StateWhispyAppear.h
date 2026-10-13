#ifndef SCN_STEP_ENEMY_SCARFY_STATEWHISPYAPPEAR_H
#define SCN_STEP_ENEMY_SCARFY_STATEWHISPYAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace scarfy {

class StateWhispyAppear : public StateBase {
public:
    StateWhispyAppear(Enemy* enemy);
    virtual ~StateWhispyAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mPhase;
    f32 mBaseY;
    f32 mRot;
};

}}}}  // namespace scn::step::enemy::scarfy

#endif
