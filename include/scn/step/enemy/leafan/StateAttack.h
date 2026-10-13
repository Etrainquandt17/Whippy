#ifndef SCN_STEP_ENEMY_LEAFAN_STATEATTACK_H
#define SCN_STEP_ENEMY_LEAFAN_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace leafan {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::leafan

#endif
