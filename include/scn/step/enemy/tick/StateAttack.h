#ifndef SCN_STEP_ENEMY_TICK_STATEATTACK_H
#define SCN_STEP_ENEMY_TICK_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tick {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::tick

#endif
