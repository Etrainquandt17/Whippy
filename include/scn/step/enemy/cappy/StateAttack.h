#ifndef SCN_STEP_ENEMY_CAPPY_STATEATTACK_H
#define SCN_STEP_ENEMY_CAPPY_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace cappy {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::cappy

#endif
