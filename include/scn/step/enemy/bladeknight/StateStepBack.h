#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATESTEPBACK_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATESTEPBACK_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bladeknight {

class StateStepBack : public StateBase {
public:
    StateStepBack(Enemy* enemy);
    virtual ~StateStepBack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::bladeknight

#endif
