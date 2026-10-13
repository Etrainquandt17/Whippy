#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATEATTACK_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bladeknight {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::bladeknight

#endif
