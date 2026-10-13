#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATEDOUBLEATTACK_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATEDOUBLEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bladeknight {

class StateDoubleAttack : public StateBase {
public:
    StateDoubleAttack(Enemy* enemy);
    virtual ~StateDoubleAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mStopCount;
};

}}}}  // namespace scn::step::enemy::bladeknight

#endif
