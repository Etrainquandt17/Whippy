#ifndef SCN_STEP_ENEMY_NEEDLOUS_STATEATTACK_H
#define SCN_STEP_ENEMY_NEEDLOUS_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace needlous {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::needlous

#endif
