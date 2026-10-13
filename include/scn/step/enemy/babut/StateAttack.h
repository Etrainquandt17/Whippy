#ifndef SCN_STEP_ENEMY_BABUT_STATEATTACK_H
#define SCN_STEP_ENEMY_BABUT_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
    u32 mDamageWait;
};

}}}}  // namespace scn::step::enemy::babut

#endif
