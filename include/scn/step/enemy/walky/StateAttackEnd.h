#ifndef SCN_STEP_ENEMY_WALKY_STATEATTACKEND_H
#define SCN_STEP_ENEMY_WALKY_STATEATTACKEND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walky {

class StateAttackEnd : public StateBase {
public:
    StateAttackEnd(Enemy* enemy);
    virtual ~StateAttackEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::walky

#endif
