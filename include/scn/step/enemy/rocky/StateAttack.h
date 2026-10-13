#ifndef SCN_STEP_ENEMY_ROCKY_STATEATTACK_H
#define SCN_STEP_ENEMY_ROCKY_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procFixPos();

private:
    s32 mFrame;
};

}}}}  // namespace scn::step::enemy::rocky

#endif
