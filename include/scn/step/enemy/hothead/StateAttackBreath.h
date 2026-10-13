#ifndef SCN_STEP_ENEMY_HOTHEAD_STATEATTACKBREATH_H
#define SCN_STEP_ENEMY_HOTHEAD_STATEATTACKBREATH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace hothead {

class StateAttackBreath : public StateBase {
public:
    StateAttackBreath(Enemy* enemy);
    virtual ~StateAttackBreath();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::hothead

#endif
